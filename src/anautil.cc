#include "anautil.h"

bool PASS() { return true; }
float UNITY() { return 1; }

//_______________________________________________________________________________________________________
RooUtil::Cutflow::Cutflow() : cuttree("Root"), last_active_cut(0), ofile(0), t(0), iseventlistbooked(false), seterrorcount(0), doskipsysthist(0), dosavettreex(0), cutflow_booked(false) { cuttreemap["Root"] = &cuttree; }

//_______________________________________________________________________________________________________
RooUtil::Cutflow::Cutflow(TFile* o) : cuttree("Root"), last_active_cut(0), ofile(o), t(0), iseventlistbooked(false), seterrorcount(0), doskipsysthist(0), dosavettreex(0), cutflow_booked(false) { cuttreemap["Root"] = &cuttree; }

//_______________________________________________________________________________________________________
RooUtil::Cutflow::~Cutflow() {}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::addToCutTreeMap(TString n) { 
if (cuttreemap.find(n.Data()) == cuttreemap.end()) cuttreemap[n.Data()] = cuttree.getCutPointer(n); 
//else RooUtil::error_exit(TString::Format("Cut %s already exists! no duplicate cut names allowed!", n.Data())); 
else abort();
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::setLastActiveCut(TString n) { last_active_cut = cuttree.getCutPointer(n); }


//_______________________________________________________________________________________________________
RooUtil::CutTree & RooUtil::Cutflow::getCut(TString n) { RooUtil::CutTree& c = cuttree.getCut(n); setLastActiveCut(n); return c; }

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::addCut(TString n, std::function<bool()> cut, std::function<float()> weight)
{
    cuttree.addCut(n);
    addToCutTreeMap(n);
    setLastActiveCut(n);
    setCut(n, cut, weight);
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::addCutToLastActiveCut(TString n, std::function<bool()> cut, std::function<float()> weight)
{
    last_active_cut->addCut(n);
    addToCutTreeMap(n);
    setLastActiveCut(n);
    setCut(n, cut, weight);
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::removeCut(TString n)
{
    CutTree* c = cuttree.getCutPointer(n);
    c->parent->children.erase(std::find(c->parent->children.begin(), c->parent->children.end(), c));
    cuttreemap.erase(cuttreemap.find(n.Data()));
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::filterCuts(std::vector<TString> ns)
{
    //
    std::vector<TString> to_not_remove;
    for (auto& n : ns)
    {
        std::vector<TString> cutlist = cuttree.getCutList(n);
        for (auto& cut : cutlist)
        {
            to_not_remove.push_back(cut);
        }
    }

    for (auto& n : ns)
    {
        std::vector<TString> cutlist = cuttree.getCutList(n);
        for (unsigned int i = 0; i < cutlist.size() - 1; ++i)
        {
            CutTree* cut = cuttree.getCutPointer(cutlist[i]);
            std::vector<CutTree*> toremove;
            for (auto& child : cut->children)
            {
                if (not child->name.EqualTo(cutlist[i+1]))
                {
                    if (std::find(to_not_remove.begin(), to_not_remove.end(), child->name) == to_not_remove.end())
                        toremove.push_back(child);
                }
            }
            for (auto& child : toremove)
            {
                cut->children.erase(std::find(cut->children.begin(), cut->children.end(), child));
                cuttreemap.erase(cuttreemap.find(child->name.Data()));
            }
        }
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::setCutLists(std::vector<TString> regions)
{
    for (auto& region : regions)
    {
        cutlists[region] = cuttree.getCutList(region);
//        std::cout << region << std::endl;
//        for (auto& cutname : cutlists[region])
//            std::cout << cutname << std::endl;
    }
    for (auto& region : regions)
    {
        for (auto& cutname : cutlists[region])
        {
            cuttreelists[region].push_back(cuttreemap[cutname.Data()]);
        }
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::addCutToSkipCutflowList(TString n)
{
    if (std::find(cutflow_nofill_cut_list.begin(), cutflow_nofill_cut_list.end(), n) == cutflow_nofill_cut_list.end())
        cutflow_nofill_cut_list.push_back(n);
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookCutflowTree()
{
    if (!t)
    {
        ofile->cd();
        t = new TTree("cut_tree", "cut_tree");
        t->SetDirectory(0);
    }
//    t->Print();
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookCutflowHistograms()
{
    if (cutflow_booked)
    {
        //RooUtil::error_exit("bookCutflowHistograms():: cutflows already booked! yet you called again to book it! Check your user code!");
        abort();
    }
    cutflow_booked = true;
    bookCutflowHistograms_v1();
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookCutflowHistograms_v2()
{
    ofile->cd();

    // Nominal
    for (auto& cuttreelist : cuttreelists)
    {
        TH1F* h     = new TH1F(cuttreelist.first + "_cutflow"   , "", cuttreelist.second.size(), 0, cuttreelist.second.size());
        TH1F* h_raw = new TH1F(cuttreelist.first + "_rawcutflow", "", cuttreelist.second.size(), 0, cuttreelist.second.size());
        h    ->Sumw2();
        h_raw->Sumw2();
        h    ->SetDirectory(0);
        h_raw->SetDirectory(0);
        std::vector<int*> passes;
        std::vector<float*> weights;
        for (auto& ct : cuttreelist.second)
        {
            passes.push_back(&(ct->pass));
            weights.push_back(&(ct->weight));
        }
        cutflow_histograms_v2   .push_back(std::make_tuple(h    , passes, weights, UNITY));
        rawcutflow_histograms_v2.push_back(std::make_tuple(h_raw, passes));
    }

    // Wgt varying systematic cutflow
    for (auto& syst : systs)
    {
        for (auto& cuttreelist : cuttreelists)
        {
            TH1F* h     = new TH1F(cuttreelist.first+syst + "_cutflow"   , "", cuttreelist.second.size(), 0, cuttreelist.second.size());
            TH1F* h_raw = new TH1F(cuttreelist.first+syst + "_rawcutflow", "", cuttreelist.second.size(), 0, cuttreelist.second.size());
            h    ->Sumw2();
            h_raw->Sumw2();
            h    ->SetDirectory(0);
            h_raw->SetDirectory(0);
            std::vector<int*> passes;
            std::vector<float*> weights;
            for (auto& ct : cuttreelist.second)
            {
                passes.push_back(&(ct->pass));
                weights.push_back(&(ct->weight));
            }
            cutflow_histograms_v2   .push_back(std::make_tuple(h    , passes, weights, systs_funcs[syst]));
            rawcutflow_histograms_v2.push_back(std::make_tuple(h_raw, passes));
        }
    }

    // Nominal
    for (unsigned int i = 0; i < cutsysts.size(); ++i)
    {
        TString cutsyst = cutsysts[i];
        for (auto& cuttreelist : cuttreelists)
        {
            TH1F* h     = new TH1F(cuttreelist.first+cutsyst + "_cutflow"   , "", cuttreelist.second.size(), 0, cuttreelist.second.size());
            TH1F* h_raw = new TH1F(cuttreelist.first+cutsyst + "_rawcutflow", "", cuttreelist.second.size(), 0, cuttreelist.second.size());
            h    ->Sumw2();
            h_raw->Sumw2();
            h    ->SetDirectory(0);
            h_raw->SetDirectory(0);
            std::vector<int*> passes;
            std::vector<float*> weights;
            for (auto& ct : cuttreelist.second)
            {
                passes.push_back(&(ct->systpasses[i]));
                weights.push_back(&(ct->systweights[i]));
            }
            cutflow_histograms_v2   .push_back(std::make_tuple(h    , passes, weights, UNITY));
            rawcutflow_histograms_v2.push_back(std::make_tuple(h_raw, passes));
        }
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookCutflowHistograms_v1()
{
    ofile->cd();

    std::tie(cutflow_histograms, rawcutflow_histograms) = RooUtil::CutflowUtil::createCutflowHistograms(cutlists);

    for (auto& syst : systs)
    {
        std::map<CUTFLOWMAPSTRING, TH1F*> cutflow_histograms_tmp;
        std::map<CUTFLOWMAPSTRING, TH1F*> rawcutflow_histograms_tmp;
        std::tie(cutflow_histograms_tmp, rawcutflow_histograms_tmp) = RooUtil::CutflowUtil::createCutflowHistograms(cutlists, syst);
        cutflow_histograms.insert(cutflow_histograms_tmp.begin(), cutflow_histograms_tmp.end());
        rawcutflow_histograms.insert(rawcutflow_histograms_tmp.begin(), rawcutflow_histograms_tmp.end());
    }

    for (auto& cutsyst : cutsysts)
    {
        std::map<CUTFLOWMAPSTRING, TH1F*> cutflow_histograms_tmp;
        std::map<CUTFLOWMAPSTRING, TH1F*> rawcutflow_histograms_tmp;
        std::tie(cutflow_histograms_tmp, rawcutflow_histograms_tmp) = RooUtil::CutflowUtil::createCutflowHistograms(cutlists, cutsyst);
        cutflow_histograms.insert(cutflow_histograms_tmp.begin(), cutflow_histograms_tmp.end());
        rawcutflow_histograms.insert(rawcutflow_histograms_tmp.begin(), rawcutflow_histograms_tmp.end());
    }

    for (auto& cutflow_histogram : cutflow_histograms)
    {
        TString msg = "Booked cutflow histogram for cut = " + cutflow_histogram.first;
        //print(msg);
    }
    for (auto& rawcutflow_histogram : rawcutflow_histograms)
    {
        TString msg = "Booked rawcutflow histogram for cut = " + rawcutflow_histogram.first;
        //print(msg);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookCutflowsForRegions(std::vector<TString> regions)
{
    setCutLists(regions);
    bookCutflowTree();
    bookCutflowHistograms();
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookCutflows()
{
    std::vector<TString> regions = cuttree.getEndCuts();
    setCutLists(regions);
    bookCutflowTree();
    bookCutflowHistograms();
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::saveOutput()
{
    saveCutflows();
    saveHistograms();
    TString filename = ofile->GetName();
    TString msg = "Wrote output to " + filename;
    //print(msg);
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::saveCutflows()
{
    // Save cutflow histograms
    ofile->cd();
    RooUtil::CutflowUtil::saveCutflowHistograms(cutflow_histograms, rawcutflow_histograms);
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::saveHistograms()
{
    ofile->cd();
    for (auto& pair : booked_histograms)
        pair.second->Write();
    for (auto& pair : booked_2dhistograms)
        pair.second->Write();
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::setCut(TString cutname, std::function<bool()> pass, std::function<float()> weight)
{
    cuttreemap[cutname.Data()]->pass_this_cut_func = pass;
    cuttreemap[cutname.Data()]->weight_this_cut_func = weight;
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::setCutSyst(TString cutname, TString syst, std::function<bool()> pass, std::function<float()> weight)
{
    if (cuttreemap[cutname.Data()]->systs.find(syst) == cuttreemap[cutname.Data()]->systs.end())
    {
        //RooUtil::error_exit(TString::Format("setCutSyst():: Did not find syst=%s from the cut=%s! Did you actually book this syst for the cut properly using addCutSyst() ?", syst.Data(), cutname.Data()));
        abort();
    }
    cuttreemap[cutname.Data()]->systs[syst]->pass_this_cut_func = pass;
    cuttreemap[cutname.Data()]->systs[syst]->weight_this_cut_func = weight;
}


//_______________________________________________________________________________________________________
void RooUtil::Cutflow::addCutSyst(TString syst, std::vector<TString> pattern, std::vector<TString> vetopattern)
{
    cutsysts.push_back(syst);
    cuttree.addSyst(syst, pattern, vetopattern);
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::addWgtSyst(TString syst, std::function<float()> weight)
{
    systs.push_back(syst);
    systs_funcs[syst] = weight;
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::fill()
{
    cuttreemap["Root"]->pass_this_cut = 1;
    cuttreemap["Root"]->weight_this_cut = 1;

    // Evaluate nominal selection cutflows (the non cut varying selections)
    cuttree.evaluate("", iseventlistbooked);

    // Nominal cutflow
    fillCutflows();

    // Wgt systematic variations
    for (auto& syst : systs) fillCutflows(syst);

    // Fill nominal histograms
    fillHistograms();

    if (not doskipsysthist)
    {
        // Wgt systematic variations
        for (auto& syst : systs) fillHistograms(syst);
    }

    for (auto& cutsyst : cutsysts)
    {
        cuttree.evaluate(cutsyst, iseventlistbooked);
        fillCutflows(cutsyst, false);
        if (not doskipsysthist)
            fillHistograms(cutsyst, false);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::fillCutflows(TString syst, bool iswgtsyst)
{
    fillCutflows_v2(syst, iswgtsyst);
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::fillCutflows_v1(TString syst, bool iswgtsyst)
{
    for (auto& pair : cutlists)
    {
        const TString& region_name = pair.first;
        std::vector<TString>& cutlist = pair.second;
        float wgtsyst = (!syst.IsNull() and iswgtsyst) ? systs_funcs[syst]() : 1;
        fillCutflow(cutlist, cutflow_histograms[(region_name+syst).Data()], rawcutflow_histograms[(region_name+syst).Data()], wgtsyst);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::fillCutflows_v2(TString syst, bool iswgtsyst)
{
    for (auto& pair : cuttreelists)
    {
        const TString& region_name = pair.first;
        std::vector<CutTree*>& cuttreelist = pair.second;
        float wgtsyst = (!syst.IsNull() and iswgtsyst) ? systs_funcs[syst]() : 1;
        fillCutflow_v2(cuttreelist, cutflow_histograms[(region_name+syst).Data()], rawcutflow_histograms[(region_name+syst).Data()], wgtsyst);
    }
}
//_______________________________________________________________________________________________________
void RooUtil::Cutflow::fillCutflow(std::vector<TString>& cutlist, TH1F* h, TH1F* hraw, float wgtsyst)
{
    for (unsigned int i = 0; i < cutlist.size(); ++i)
    {
        int& pass = cuttreemap[cutlist[i].Data()]->pass;
        if (pass)
        {
            float& weight = cuttreemap[cutlist[i].Data()]->weight;
            h->Fill(i, weight * wgtsyst);
            hraw->Fill(i, 1);
        }
        else
        {
            return;
        }
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::fillCutflow_v2(std::vector<CutTree*>& cuttreelist, TH1F* h, TH1F* hraw, float wgtsyst)
{
    for (unsigned int i = 0; i < cuttreelist.size(); ++i)
    {
        CutTree* ct = cuttreelist[i];
        // if (std::find(cutflow_nofill_cut_list.begin(), cutflow_nofill_cut_list.end(), ct->name) != cutflow_nofill_cut_list.end())
        //     continue;
        int& pass = ct->pass;
        if (pass)
        {
            float& weight = ct->weight;
            h->Fill(i, weight * wgtsyst);
            hraw->Fill(i, 1);
        }
        else
        {
            return;
        }
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::fillHistograms(TString syst, bool iswgtsyst)
{

    float wgtsyst = (!syst.IsNull() and iswgtsyst) ? systs_funcs[syst]() : 1;
    cuttree.fillHistograms(syst, wgtsyst);
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookHistograms(Histograms& histograms)
{
    std::vector<TString> regions = cuttree.getEndCuts();
    for (auto& region : regions)
    {
        std::vector<TString> cutlist = cuttree.getCutList(region);
        bookHistograms(histograms, cutlist);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookHistograms(Histograms& histograms, std::vector<TString> cutlist)
{
    for (auto& cut : cutlist)
    {
        bookHistogramsForCut(histograms, cut);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookHistogram(TString cut, std::pair<TString, std::tuple<unsigned, float, float, std::function<float()>, TString>> key, TString syst)
{
    TString varname = key.first;
    unsigned int nbin = std::get<0>(key.second);
    float min = std::get<1>(key.second);
    float max = std::get<2>(key.second);
    TString title = std::get<4>(key.second);
    std::function<float()> vardef = std::get<3>(key.second);
    TString histname = cut + syst + "__" + varname;
    if (booked_histograms.find(std::make_tuple(cut.Data(), syst.Data(), varname.Data())) == booked_histograms.end())
    {
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())] = new TH1F(histname, title, nbin, min, max);
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())]->SetDirectory(0);
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())]->Sumw2();
        if (syst.IsNull())
        {
            booked_histograms_nominal_keys.push_back(std::make_tuple(cut.Data(), syst.Data(), varname.Data()));
        }
        cuttreemap[cut.Data()]->addHist1D(booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())], vardef, syst);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookVecHistogram(TString cut, std::pair<TString, std::tuple<unsigned, float, float, std::function<std::vector<float>()>, std::function<std::vector<float>()>>> key, TString syst)
{
    TString varname = key.first;
    unsigned int nbin = std::get<0>(key.second);
    float min = std::get<1>(key.second);
    float max = std::get<2>(key.second);
    std::function<std::vector<float>()> vardef = std::get<3>(key.second);
    std::function<std::vector<float>()> wgtdef = std::get<4>(key.second);
    TString histname = cut + syst + "__" + varname;
    if (booked_histograms.find(std::make_tuple(cut.Data(), syst.Data(), varname.Data())) == booked_histograms.end())
    {
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())] = new TH1F(histname, "", nbin, min, max);
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())]->SetDirectory(0);
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())]->Sumw2();
        if (syst.IsNull())
        {
            booked_histograms_nominal_keys.push_back(std::make_tuple(cut.Data(), syst.Data(), varname.Data()));
        }
        cuttreemap[cut.Data()]->addHist1DVec(booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())], vardef, wgtdef, syst);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookHistogram(TString cut, std::pair<TString, std::tuple<std::vector<float>, std::function<float()>, TString>> key, TString syst)
{
    TString varname = key.first;
    std::vector<float> boundaries = std::get<0>(key.second);
    std::function<float()> vardef = std::get<1>(key.second);
    TString title = std::get<2>(key.second);
    TString histname = cut + syst + "__" + varname;
    if (booked_histograms.find(std::make_tuple(cut.Data(), syst.Data(), varname.Data())) == booked_histograms.end())
    {
        Float_t bounds[boundaries.size()];
        for (unsigned int i = 0; i < boundaries.size(); ++i)
            bounds[i] = boundaries[i];
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())] = new TH1F(histname, title, boundaries.size()-1, bounds);
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())]->SetDirectory(0);
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())]->Sumw2();
        if (syst.IsNull())
        {
            booked_histograms_nominal_keys.push_back(std::make_tuple(cut.Data(), syst.Data(), varname.Data()));
        }
        cuttreemap[cut.Data()]->addHist1D(booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())], vardef, syst);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookVecHistogram(TString cut, std::pair<TString, std::tuple<std::vector<float>, std::function<std::vector<float>()>, std::function<std::vector<float>()>>> key, TString syst)
{
    TString varname = key.first;
    std::vector<float> boundaries = std::get<0>(key.second);
    std::function<std::vector<float>()> vardef = std::get<1>(key.second);
    std::function<std::vector<float>()> wgtdef = std::get<2>(key.second);
    TString histname = cut + syst + "__" + varname;
    if (booked_histograms.find(std::make_tuple(cut.Data(), syst.Data(), varname.Data())) == booked_histograms.end())
    {
        Float_t bounds[boundaries.size()];
        for (unsigned int i = 0; i < boundaries.size(); ++i)
            bounds[i] = boundaries[i];
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())] = new TH1F(histname, "", boundaries.size()-1, bounds);
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())]->SetDirectory(0);
        booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())]->Sumw2();
        if (syst.IsNull())
        {
            booked_histograms_nominal_keys.push_back(std::make_tuple(cut.Data(), syst.Data(), varname.Data()));
        }
        cuttreemap[cut.Data()]->addHist1DVec(booked_histograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data())], vardef, wgtdef, syst);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::book2DHistogram(TString cut, std::pair<std::pair<TString, TString>, std::tuple<TString, unsigned, float, float, unsigned, float, float, std::function<float()>, std::function<float()>>> key, TString syst)
{
    TString varname = key.first.first;
    TString varnamey = key.first.second;
    TString title = std::get<0>(key.second);
    unsigned int nbin = std::get<1>(key.second);
    float min = std::get<2>(key.second);
    float max = std::get<3>(key.second);
    unsigned int nbiny = std::get<4>(key.second);
    float miny = std::get<5>(key.second);
    float maxy = std::get<6>(key.second);
    std::function<float()> varxdef = std::get<7>(key.second);
    std::function<float()> varydef = std::get<8>(key.second);
    TString histname = cut + syst + "__" + varname+"_v_"+varnamey;
    if (booked_2dhistograms.find(std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())) == booked_2dhistograms.end())
    {
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())] = new TH2F(histname, title, nbin, min, max, nbiny, miny, maxy);
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())]->SetDirectory(0);
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())]->Sumw2();
        if (syst.IsNull())
        {
            booked_2dhistograms_nominal_keys.push_back(std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data()));
        }
        cuttreemap[cut.Data()]->addHist2D(booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())], varxdef, varydef, syst);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::book2DVecHistogram(TString cut, std::pair<std::pair<TString, TString>, std::tuple<unsigned, float, float, unsigned, float, float, std::function<std::vector<float>()>, std::function<std::vector<float>()>, std::function<std::vector<float>()>>> key, TString syst)
{
    TString varname = key.first.first;
    TString varnamey = key.first.second;
    unsigned int nbin = std::get<0>(key.second);
    float min = std::get<1>(key.second);
    float max = std::get<2>(key.second);
    unsigned int nbiny = std::get<3>(key.second);
    float miny = std::get<4>(key.second);
    float maxy = std::get<5>(key.second);
    std::function<std::vector<float>()> varxdef = std::get<6>(key.second);
    std::function<std::vector<float>()> varydef = std::get<7>(key.second);
    std::function<std::vector<float>()> elemwgt = std::get<8>(key.second);
    TString histname = cut + syst + "__" + varname+"_v_"+varnamey;
    if (booked_2dhistograms.find(std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())) == booked_2dhistograms.end())
    {
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())] = new TH2F(histname, "", nbin, min, max, nbiny, miny, maxy);
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())]->SetDirectory(0);
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())]->Sumw2();
        if (syst.IsNull())
        {
            booked_2dhistograms_nominal_keys.push_back(std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data()));
        }
        cuttreemap[cut.Data()]->addHist2DVec(booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())], varxdef, varydef, elemwgt, syst);
    }
}
//_______________________________________________________________________________________________________
void RooUtil::Cutflow::book2DVecHistogram(TString cut, std::pair<std::pair<TString, TString>, std::tuple<std::vector<float>, unsigned, float, float, std::function<std::vector<float>()>, std::function<std::vector<float>()>, std::function<std::vector<float>()>>> key, TString syst)
{
    TString varname = key.first.first;
    TString varnamey = key.first.second;
    std::vector<float> xboundaries = std::get<0>(key.second);
    unsigned int nbiny = std::get<1>(key.second);
    float miny = std::get<2>(key.second);
    float maxy = std::get<3>(key.second);
    std::function<std::vector<float>()> varxdef = std::get<4>(key.second);
    std::function<std::vector<float>()> varydef = std::get<5>(key.second);
    std::function<std::vector<float>()> elemwgt = std::get<6>(key.second);
    TString histname = cut + syst + "__" + varname+"_v_"+varnamey;
    if (booked_2dhistograms.find(std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())) == booked_2dhistograms.end())
    {
        Double_t xbounds[xboundaries.size()];
        for (unsigned int i = 0; i < xboundaries.size(); ++i)
            xbounds[i] = xboundaries[i];
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())] = new TH2F(histname, "", xboundaries.size() - 1, xbounds, nbiny, miny, maxy);
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())]->SetDirectory(0);
        booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())]->Sumw2();
        if (syst.IsNull())
        {
            booked_2dhistograms_nominal_keys.push_back(std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data()));
        }
        cuttreemap[cut.Data()]->addHist2DVec(booked_2dhistograms[std::make_tuple(cut.Data(), syst.Data(), varname.Data(), varnamey.Data())], varxdef, varydef, elemwgt, syst);
    }
}
//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookHistogramsForCut(Histograms& histograms, TString cut)
{
    for (auto& key : histograms.th1fs)           bookHistogram     (cut, key);
    for (auto& key : histograms.th1fs_varbin)    bookHistogram     (cut, key);
    for (auto& key : histograms.th1vecfs)        bookVecHistogram  (cut, key);
    for (auto& key : histograms.th1vecfs_varbin) bookVecHistogram  (cut, key);
    for (auto& key : histograms.th2fs)           book2DHistogram   (cut, key);
    for (auto& key : histograms.th2vecfs)        book2DVecHistogram(cut, key);
    for (auto& key : histograms.th2vecfs_xvarbin)book2DVecHistogram(cut, key);
    if (not doskipsysthist)
    {
        for (auto& syst : systs)
        {
            for (auto& key : histograms.th1fs)           bookHistogram     (cut, key, syst);
            for (auto& key : histograms.th1fs_varbin)    bookHistogram     (cut, key, syst);
            for (auto& key : histograms.th1vecfs)        bookVecHistogram  (cut, key, syst);
            for (auto& key : histograms.th1vecfs_varbin) bookVecHistogram  (cut, key, syst);
            for (auto& key : histograms.th2fs)           book2DHistogram   (cut, key, syst);
            for (auto& key : histograms.th2vecfs)        book2DVecHistogram(cut, key, syst);
            for (auto& key : histograms.th2vecfs_xvarbin)book2DVecHistogram(cut, key, syst);
        }
        for (auto& cutsyst : cutsysts)
        {
            for (auto& key : histograms.th1fs)           bookHistogram     (cut, key, cutsyst);
            for (auto& key : histograms.th1fs_varbin)    bookHistogram     (cut, key, cutsyst);
            for (auto& key : histograms.th1vecfs)        bookVecHistogram  (cut, key, cutsyst);
            for (auto& key : histograms.th1vecfs_varbin) bookVecHistogram  (cut, key, cutsyst);
            for (auto& key : histograms.th2fs)           book2DHistogram   (cut, key, cutsyst);
            for (auto& key : histograms.th2vecfs)        book2DVecHistogram(cut, key, cutsyst);
            for (auto& key : histograms.th2vecfs_xvarbin)book2DVecHistogram(cut, key, cutsyst);
        }
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookHistogramsForCutAndBelow(Histograms& histograms, TString cut)
{
    std::vector<TString> cutlist = cuttree.getCutListBelow(cut);
    for (auto& c : cutlist)
    {
        bookHistogramsForCut(histograms, c);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::bookHistogramsForEndCuts(Histograms& histograms)
{
    std::vector<TString> regions = cuttree.getEndCuts();
    for (auto& region : regions)
    {
        bookHistogramsForCut(histograms, region);
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::setSkipSystematicHistograms(bool v)
{
    doskipsysthist = v;
}

//_______________________________________________________________________________________________________
void RooUtil::Cutflow::setHistsAxesExtendable()
{
    for (auto& pair : booked_histograms)
        pair.second->SetCanExtend(TH1::kAllAxes);
}

//_______________________________________________________________________________________________________
RooUtil::Histograms::Histograms()
{
}

//_______________________________________________________________________________________________________
RooUtil::Histograms::~Histograms()
{
}

//_______________________________________________________________________________________________________
void RooUtil::Histograms::addHistogram(TString name, TString title, unsigned int n, float min, float max, std::function<float()> vardef)
{
    if (th1fs.find(name) == th1fs.end())
    {
        th1fs[name] = std::make_tuple(n, min, max, vardef, title);
    }
    else
    {
        //RooUtil::error_exit(TString::Format("histogram already exists name = %s", name.Data()));
        abort();
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Histograms::addVecHistogram(TString name, unsigned int n, float min, float max, std::function<std::vector<float>()> vardef, std::function<std::vector<float>()> wgt)
{
    if (th1vecfs.find(name) == th1vecfs.end())
    {
        th1vecfs[name] = std::make_tuple(n, min, max, vardef, wgt);
    }
    else
    {
        //RooUtil::error_exit(TString::Format("histogram already exists name = %s", name.Data()));
        abort();
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Histograms::addHistogram(TString name, TString title, std::vector<float> boundaries, std::function<float()> vardef)
{
    if (th1fs_varbin.find(name) == th1fs_varbin.end())
    {
        th1fs_varbin[name] = std::make_tuple(boundaries, vardef, title);
    }
    else
    {
        //RooUtil::error_exit(TString::Format("histogram already exists name = %s", name.Data()));
       abort();
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Histograms::addVecHistogram(TString name, std::vector<float> boundaries, std::function<std::vector<float>()> vardef, std::function<std::vector<float>()> wgt)
{
    if (th1vecfs_varbin.find(name) == th1vecfs_varbin.end())
    {
        th1vecfs_varbin[name] = std::make_tuple(boundaries, vardef, wgt);
    }
    else
    {
        //RooUtil::error_exit(TString::Format("histogram already exists name = %s", name.Data()));
        abort();
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Histograms::add2DHistogram(TString title, TString name, unsigned int n, float min, float max, TString namey, unsigned int ny, float miny, float maxy, std::function<float()> varxdef, std::function<float()> varydef)
{
    if (th2fs.find(std::make_pair(name, namey)) == th2fs.end())
    {
        th2fs[std::make_pair(name, namey)] = std::make_tuple(title, n, min, max, ny, miny, maxy, varxdef, varydef);
    }
    else
    {
        //RooUtil::error_exit(TString::Format("histogram already exists name = %s", (name+"_v_"+namey).Data()));
        abort();
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Histograms::add2DVecHistogram(TString name, unsigned int n, float min, float max, TString namey, unsigned int ny, float miny, float maxy, std::function<std::vector<float>()> varxdef, std::function<std::vector<float>()> varydef, std::function<std::vector<float>()> elem_wgt)
{
    if (th2vecfs.find(std::make_pair(name, namey)) == th2vecfs.end())
    {
        th2vecfs[std::make_pair(name, namey)] = std::make_tuple(n, min, max, ny, miny, maxy, varxdef, varydef, elem_wgt);
    }
    else
    {
        //RooUtil::error_exit(TString::Format("histogram already exists name = %s", (name+"_v_"+namey).Data()));
        abort();
    }
}

//_______________________________________________________________________________________________________
void RooUtil::Histograms::add2DVecHistogram(TString name, std::vector<float> xboundaries, TString namey, unsigned int ny, float miny, float maxy, std::function<std::vector<float>()> varxdef, std::function<std::vector<float>()> varydef, std::function<std::vector<float>()> elem_wgt)
{
    if (th2vecfs_xvarbin.find(std::make_pair(name, namey)) == th2vecfs_xvarbin.end())
    {
        th2vecfs_xvarbin[std::make_pair(name, namey)] = std::make_tuple(xboundaries, ny, miny, maxy, varxdef, varydef, elem_wgt);
    }
    else
    {
        //RooUtil::error_exit(TString::Format("histogram already exists name = %s", (name+"_v_"+namey).Data()));
        abort();
    }
}

