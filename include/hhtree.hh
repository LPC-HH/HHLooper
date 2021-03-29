#ifndef hhtree_HH
#include <TBranch.h> 
#include <TTree.h> 
#include <TH1F.h> 
#include <TFile.h> 
#include <TBits.h> 
#include <vector> 
#include <unistd.h> 
using namespace std; 

class hhtree{
 private:
 protected:
   unsigned int index;
   float weight_;
   TBranch *weight_branch;
   bool weight_isLoaded;
   float genMTT_;
   TBranch *genMTT_branch;
   bool genMTT_isLoaded;
   float triggerEffWeight_;
   TBranch *triggerEffWeight_branch;
   bool triggerEffWeight_isLoaded;
   float triggerEff3DWeight_;
   TBranch *triggerEff3DWeight_branch;
   bool triggerEff3DWeight_isLoaded;
   float triggerEffMCWeight_;
   TBranch *triggerEffMCWeight_branch;
   bool triggerEffMCWeight_isLoaded;
   float triggerEffMC3DWeight_;
   TBranch *triggerEffMC3DWeight_branch;
   bool triggerEffMC3DWeight_isLoaded;
   float pileupWeight_;
   TBranch *pileupWeight_branch;
   bool pileupWeight_isLoaded;
   float pileupWeightUp_;
   TBranch *pileupWeightUp_branch;
   bool pileupWeightUp_isLoaded;
   float pileupWeightDown_;
   TBranch *pileupWeightDown_branch;
   bool pileupWeightDown_isLoaded;
   float totalWeight_;
   TBranch *totalWeight_branch;
   bool totalWeight_isLoaded;
   unsigned int run_;
   TBranch *run_branch;
   bool run_isLoaded;
   unsigned int lumi_;
   TBranch *lumi_branch;
   bool lumi_isLoaded;
   unsigned long int event_;
   TBranch *event_branch;
   bool event_isLoaded;
   float npu_;
   TBranch *npu_branch;
   bool npu_isLoaded;
   float rho_;
   TBranch *rho_branch;
   bool rho_isLoaded;
   int NJets_;
   TBranch *NJets_branch;
   bool NJets_isLoaded;
   float MET_;
   TBranch *MET_branch;
   bool MET_isLoaded;
   float fatJet1Pt_;
   TBranch *fatJet1Pt_branch;
   bool fatJet1Pt_isLoaded;
   float fatJet1Pt_JES_Up_;
   TBranch *fatJet1Pt_JES_Up_branch;
   bool fatJet1Pt_JES_Up_isLoaded;
   float fatJet1Pt_JES_Down_;
   TBranch *fatJet1Pt_JES_Down_branch;
   bool fatJet1Pt_JES_Down_isLoaded;
   float fatJet1Eta_;
   TBranch *fatJet1Eta_branch;
   bool fatJet1Eta_isLoaded;
   float fatJet1Phi_;
   TBranch *fatJet1Phi_branch;
   bool fatJet1Phi_isLoaded;
   float fatJet1Mass_;
   TBranch *fatJet1Mass_branch;
   bool fatJet1Mass_isLoaded;
   float fatJet1MassSD_;
   TBranch *fatJet1MassSD_branch;
   bool fatJet1MassSD_isLoaded;
   float fatJet1MassSD_UnCorrected_;
   TBranch *fatJet1MassSD_UnCorrected_branch;
   bool fatJet1MassSD_UnCorrected_isLoaded;
   float fatJet1MassSD_JMS_Up_;
   TBranch *fatJet1MassSD_JMS_Up_branch;
   bool fatJet1MassSD_JMS_Up_isLoaded;
   float fatJet1MassSD_JMS_Down_;
   TBranch *fatJet1MassSD_JMS_Down_branch;
   bool fatJet1MassSD_JMS_Down_isLoaded;
   float fatJet1MassSD_JMR_Up_;
   TBranch *fatJet1MassSD_JMR_Up_branch;
   bool fatJet1MassSD_JMR_Up_isLoaded;
   float fatJet1MassSD_JMR_Down_;
   TBranch *fatJet1MassSD_JMR_Down_branch;
   bool fatJet1MassSD_JMR_Down_isLoaded;
   float fatJet1DDBTagger_;
   TBranch *fatJet1DDBTagger_branch;
   bool fatJet1DDBTagger_isLoaded;
   float fatJet1PNetXbb_;
   TBranch *fatJet1PNetXbb_branch;
   bool fatJet1PNetXbb_isLoaded;
   float fatJet1PNetQCDb_;
   TBranch *fatJet1PNetQCDb_branch;
   bool fatJet1PNetQCDb_isLoaded;
   float fatJet1PNetQCDbb_;
   TBranch *fatJet1PNetQCDbb_branch;
   bool fatJet1PNetQCDbb_isLoaded;
   float fatJet1PNetQCDc_;
   TBranch *fatJet1PNetQCDc_branch;
   bool fatJet1PNetQCDc_isLoaded;
   float fatJet1PNetQCDcc_;
   TBranch *fatJet1PNetQCDcc_branch;
   bool fatJet1PNetQCDcc_isLoaded;
   float fatJet1PNetQCDothers_;
   TBranch *fatJet1PNetQCDothers_branch;
   bool fatJet1PNetQCDothers_isLoaded;
   float fatJet1_deepTagMD_W_;
   TBranch *fatJet1_deepTagMD_W_branch;
   bool fatJet1_deepTagMD_W_isLoaded;
   float fatJet1_deepTagMD_Z_;
   TBranch *fatJet1_deepTagMD_Z_branch;
   bool fatJet1_deepTagMD_Z_isLoaded;
   float fatJet1_deepTag_W_;
   TBranch *fatJet1_deepTag_W_branch;
   bool fatJet1_deepTag_W_isLoaded;
   float fatJet1_deepTag_Z_;
   TBranch *fatJet1_deepTag_Z_branch;
   bool fatJet1_deepTag_Z_isLoaded;
   int fatJet1GenMatchIndex_;
   TBranch *fatJet1GenMatchIndex_branch;
   bool fatJet1GenMatchIndex_isLoaded;
   float fatJet1Tau3OverTau2_;
   TBranch *fatJet1Tau3OverTau2_branch;
   bool fatJet1Tau3OverTau2_isLoaded;
   float fatJet1_n2b1_;
   TBranch *fatJet1_n2b1_branch;
   bool fatJet1_n2b1_isLoaded;
   bool fatJet1HasMuon_;
   TBranch *fatJet1HasMuon_branch;
   bool fatJet1HasMuon_isLoaded;
   bool fatJet1HasElectron_;
   TBranch *fatJet1HasElectron_branch;
   bool fatJet1HasElectron_isLoaded;
   bool fatJet1HasBJetCSVLoose_;
   TBranch *fatJet1HasBJetCSVLoose_branch;
   bool fatJet1HasBJetCSVLoose_isLoaded;
   bool fatJet1HasBJetCSVMedium_;
   TBranch *fatJet1HasBJetCSVMedium_branch;
   bool fatJet1HasBJetCSVMedium_isLoaded;
   bool fatJet1HasBJetCSVTight_;
   TBranch *fatJet1HasBJetCSVTight_branch;
   bool fatJet1HasBJetCSVTight_isLoaded;
   bool fatJet1OppositeHemisphereHasBJet_;
   TBranch *fatJet1OppositeHemisphereHasBJet_branch;
   bool fatJet1OppositeHemisphereHasBJet_isLoaded;
   int isVBFtag_;
   TBranch *isVBFtag_branch;
   bool isVBFtag_isLoaded;
   float dijetmass_;
   TBranch *dijetmass_branch;
   bool dijetmass_isLoaded;
   float vbfjet1Pt_;
   TBranch *vbfjet1Pt_branch;
   bool vbfjet1Pt_isLoaded;
   float vbfjet1Eta_;
   TBranch *vbfjet1Eta_branch;
   bool vbfjet1Eta_isLoaded;
   float vbfjet1Phi_;
   TBranch *vbfjet1Phi_branch;
   bool vbfjet1Phi_isLoaded;
   float vbfjet1Mass_;
   TBranch *vbfjet1Mass_branch;
   bool vbfjet1Mass_isLoaded;
   float vbfjet2Pt_;
   TBranch *vbfjet2Pt_branch;
   bool vbfjet2Pt_isLoaded;
   float vbfjet2Eta_;
   TBranch *vbfjet2Eta_branch;
   bool vbfjet2Eta_isLoaded;
   float vbfjet2Phi_;
   TBranch *vbfjet2Phi_branch;
   bool vbfjet2Phi_isLoaded;
   float vbfjet2Mass_;
   TBranch *vbfjet2Mass_branch;
   bool vbfjet2Mass_isLoaded;
   float vbffatJet1PNetXbb_;
   TBranch *vbffatJet1PNetXbb_branch;
   bool vbffatJet1PNetXbb_isLoaded;
   float vbffatJet1Pt_;
   TBranch *vbffatJet1Pt_branch;
   bool vbffatJet1Pt_isLoaded;
   float vbffatJet1Eta_;
   TBranch *vbffatJet1Eta_branch;
   bool vbffatJet1Eta_isLoaded;
   float vbffatJet1Phi_;
   TBranch *vbffatJet1Phi_branch;
   bool vbffatJet1Phi_isLoaded;
   float vbffatJet2PNetXbb_;
   TBranch *vbffatJet2PNetXbb_branch;
   bool vbffatJet2PNetXbb_isLoaded;
   float vbffatJet2Pt_;
   TBranch *vbffatJet2Pt_branch;
   bool vbffatJet2Pt_isLoaded;
   float vbffatJet2Eta_;
   TBranch *vbffatJet2Eta_branch;
   bool vbffatJet2Eta_isLoaded;
   float vbffatJet2Phi_;
   TBranch *vbffatJet2Phi_branch;
   bool vbffatJet2Phi_isLoaded;
   float genHiggs1Pt_;
   TBranch *genHiggs1Pt_branch;
   bool genHiggs1Pt_isLoaded;
   float genHiggs1Eta_;
   TBranch *genHiggs1Eta_branch;
   bool genHiggs1Eta_isLoaded;
   float genHiggs1Phi_;
   TBranch *genHiggs1Phi_branch;
   bool genHiggs1Phi_isLoaded;
   float genHiggs2Pt_;
   TBranch *genHiggs2Pt_branch;
   bool genHiggs2Pt_isLoaded;
   float genHiggs2Eta_;
   TBranch *genHiggs2Eta_branch;
   bool genHiggs2Eta_isLoaded;
   float genHiggs2Phi_;
   TBranch *genHiggs2Phi_branch;
   bool genHiggs2Phi_isLoaded;
   float genHH_pt_;
   TBranch *genHH_pt_branch;
   bool genHH_pt_isLoaded;
   float genHH_eta_;
   TBranch *genHH_eta_branch;
   bool genHH_eta_isLoaded;
   float genHH_phi_;
   TBranch *genHH_phi_branch;
   bool genHH_phi_isLoaded;
   float genHH_mass_;
   TBranch *genHH_mass_branch;
   bool genHH_mass_isLoaded;
   int genLeptonId_;
   TBranch *genLeptonId_branch;
   bool genLeptonId_isLoaded;
   int genLeptonMotherId_;
   TBranch *genLeptonMotherId_branch;
   bool genLeptonMotherId_isLoaded;
   float genLeptonPt_;
   TBranch *genLeptonPt_branch;
   bool genLeptonPt_isLoaded;
   float genLeptonEta_;
   TBranch *genLeptonEta_branch;
   bool genLeptonEta_isLoaded;
   float genLeptonPhi_;
   TBranch *genLeptonPhi_branch;
   bool genLeptonPhi_isLoaded;
   float fatJet2Pt_;
   TBranch *fatJet2Pt_branch;
   bool fatJet2Pt_isLoaded;
   float fatJet2Pt_JES_Up_;
   TBranch *fatJet2Pt_JES_Up_branch;
   bool fatJet2Pt_JES_Up_isLoaded;
   float fatJet2Pt_JES_Down_;
   TBranch *fatJet2Pt_JES_Down_branch;
   bool fatJet2Pt_JES_Down_isLoaded;
   float fatJet2Eta_;
   TBranch *fatJet2Eta_branch;
   bool fatJet2Eta_isLoaded;
   float fatJet2Phi_;
   TBranch *fatJet2Phi_branch;
   bool fatJet2Phi_isLoaded;
   float fatJet2Mass_;
   TBranch *fatJet2Mass_branch;
   bool fatJet2Mass_isLoaded;
   float fatJet2MassSD_;
   TBranch *fatJet2MassSD_branch;
   bool fatJet2MassSD_isLoaded;
   float fatJet2MassSD_UnCorrected_;
   TBranch *fatJet2MassSD_UnCorrected_branch;
   bool fatJet2MassSD_UnCorrected_isLoaded;
   float fatJet2MassSD_JMS_Up_;
   TBranch *fatJet2MassSD_JMS_Up_branch;
   bool fatJet2MassSD_JMS_Up_isLoaded;
   float fatJet2MassSD_JMS_Down_;
   TBranch *fatJet2MassSD_JMS_Down_branch;
   bool fatJet2MassSD_JMS_Down_isLoaded;
   float fatJet2MassSD_JMR_Up_;
   TBranch *fatJet2MassSD_JMR_Up_branch;
   bool fatJet2MassSD_JMR_Up_isLoaded;
   float fatJet2MassSD_JMR_Down_;
   TBranch *fatJet2MassSD_JMR_Down_branch;
   bool fatJet2MassSD_JMR_Down_isLoaded;
   float fatJet2DDBTagger_;
   TBranch *fatJet2DDBTagger_branch;
   bool fatJet2DDBTagger_isLoaded;
   float fatJet2PNetXbb_;
   TBranch *fatJet2PNetXbb_branch;
   bool fatJet2PNetXbb_isLoaded;
   float fatJet2PNetQCDb_;
   TBranch *fatJet2PNetQCDb_branch;
   bool fatJet2PNetQCDb_isLoaded;
   float fatJet2PNetQCDbb_;
   TBranch *fatJet2PNetQCDbb_branch;
   bool fatJet2PNetQCDbb_isLoaded;
   float fatJet2PNetQCDc_;
   TBranch *fatJet2PNetQCDc_branch;
   bool fatJet2PNetQCDc_isLoaded;
   float fatJet2PNetQCDcc_;
   TBranch *fatJet2PNetQCDcc_branch;
   bool fatJet2PNetQCDcc_isLoaded;
   float fatJet2PNetQCDothers_;
   TBranch *fatJet2PNetQCDothers_branch;
   bool fatJet2PNetQCDothers_isLoaded;
   float fatJet2_deepTagMD_W_;
   TBranch *fatJet2_deepTagMD_W_branch;
   bool fatJet2_deepTagMD_W_isLoaded;
   float fatJet2_deepTagMD_Z_;
   TBranch *fatJet2_deepTagMD_Z_branch;
   bool fatJet2_deepTagMD_Z_isLoaded;
   float fatJet2_deepTag_W_;
   TBranch *fatJet2_deepTag_W_branch;
   bool fatJet2_deepTag_W_isLoaded;
   float fatJet2_deepTag_Z_;
   TBranch *fatJet2_deepTag_Z_branch;
   bool fatJet2_deepTag_Z_isLoaded;
   int fatJet2GenMatchIndex_;
   TBranch *fatJet2GenMatchIndex_branch;
   bool fatJet2GenMatchIndex_isLoaded;
   float fatJet2Tau3OverTau2_;
   TBranch *fatJet2Tau3OverTau2_branch;
   bool fatJet2Tau3OverTau2_isLoaded;
   bool fatJet2HasMuon_;
   TBranch *fatJet2HasMuon_branch;
   bool fatJet2HasMuon_isLoaded;
   bool fatJet2HasElectron_;
   TBranch *fatJet2HasElectron_branch;
   bool fatJet2HasElectron_isLoaded;
   bool fatJet2HasBJetCSVLoose_;
   TBranch *fatJet2HasBJetCSVLoose_branch;
   bool fatJet2HasBJetCSVLoose_isLoaded;
   bool fatJet2HasBJetCSVMedium_;
   TBranch *fatJet2HasBJetCSVMedium_branch;
   bool fatJet2HasBJetCSVMedium_isLoaded;
   bool fatJet2HasBJetCSVTight_;
   TBranch *fatJet2HasBJetCSVTight_branch;
   bool fatJet2HasBJetCSVTight_isLoaded;
   float fatJet3Pt_;
   TBranch *fatJet3Pt_branch;
   bool fatJet3Pt_isLoaded;
   float fatJet3Eta_;
   TBranch *fatJet3Eta_branch;
   bool fatJet3Eta_isLoaded;
   float fatJet3Phi_;
   TBranch *fatJet3Phi_branch;
   bool fatJet3Phi_isLoaded;
   float fatJet3Mass_;
   TBranch *fatJet3Mass_branch;
   bool fatJet3Mass_isLoaded;
   float fatJet3MassSD_;
   TBranch *fatJet3MassSD_branch;
   bool fatJet3MassSD_isLoaded;
   float fatJet3DDBTagger_;
   TBranch *fatJet3DDBTagger_branch;
   bool fatJet3DDBTagger_isLoaded;
   float fatJet3PNetXbb_;
   TBranch *fatJet3PNetXbb_branch;
   bool fatJet3PNetXbb_isLoaded;
   float fatJet3PNetQCDb_;
   TBranch *fatJet3PNetQCDb_branch;
   bool fatJet3PNetQCDb_isLoaded;
   float fatJet3PNetQCDbb_;
   TBranch *fatJet3PNetQCDbb_branch;
   bool fatJet3PNetQCDbb_isLoaded;
   float fatJet3PNetQCDc_;
   TBranch *fatJet3PNetQCDc_branch;
   bool fatJet3PNetQCDc_isLoaded;
   float fatJet3PNetQCDcc_;
   TBranch *fatJet3PNetQCDcc_branch;
   bool fatJet3PNetQCDcc_isLoaded;
   float fatJet3PNetQCDothers_;
   TBranch *fatJet3PNetQCDothers_branch;
   bool fatJet3PNetQCDothers_isLoaded;
   float fatJet3Tau3OverTau2_;
   TBranch *fatJet3Tau3OverTau2_branch;
   bool fatJet3Tau3OverTau2_isLoaded;
   bool fatJet3HasMuon_;
   TBranch *fatJet3HasMuon_branch;
   bool fatJet3HasMuon_isLoaded;
   bool fatJet3HasElectron_;
   TBranch *fatJet3HasElectron_branch;
   bool fatJet3HasElectron_isLoaded;
   bool fatJet3HasBJetCSVLoose_;
   TBranch *fatJet3HasBJetCSVLoose_branch;
   bool fatJet3HasBJetCSVLoose_isLoaded;
   bool fatJet3HasBJetCSVMedium_;
   TBranch *fatJet3HasBJetCSVMedium_branch;
   bool fatJet3HasBJetCSVMedium_isLoaded;
   bool fatJet3HasBJetCSVTight_;
   TBranch *fatJet3HasBJetCSVTight_branch;
   bool fatJet3HasBJetCSVTight_isLoaded;
   float hh_pt_;
   TBranch *hh_pt_branch;
   bool hh_pt_isLoaded;
   float hh_eta_;
   TBranch *hh_eta_branch;
   bool hh_eta_isLoaded;
   float hh_phi_;
   TBranch *hh_phi_branch;
   bool hh_phi_isLoaded;
   float hh_mass_;
   TBranch *hh_mass_branch;
   bool hh_mass_isLoaded;
   float hh_pt_JESUp_;
   TBranch *hh_pt_JESUp_branch;
   bool hh_pt_JESUp_isLoaded;
   float hh_pt_JESDown_;
   TBranch *hh_pt_JESDown_branch;
   bool hh_pt_JESDown_isLoaded;
   float hh_pt_JMSUp_;
   TBranch *hh_pt_JMSUp_branch;
   bool hh_pt_JMSUp_isLoaded;
   float hh_pt_JMSDown_;
   TBranch *hh_pt_JMSDown_branch;
   bool hh_pt_JMSDown_isLoaded;
   float hh_pt_JMRUp_;
   TBranch *hh_pt_JMRUp_branch;
   bool hh_pt_JMRUp_isLoaded;
   float hh_pt_JMRDown_;
   TBranch *hh_pt_JMRDown_branch;
   bool hh_pt_JMRDown_isLoaded;
   float hh_eta_JESUp_;
   TBranch *hh_eta_JESUp_branch;
   bool hh_eta_JESUp_isLoaded;
   float hh_eta_JESDown_;
   TBranch *hh_eta_JESDown_branch;
   bool hh_eta_JESDown_isLoaded;
   float hh_eta_JMSUp_;
   TBranch *hh_eta_JMSUp_branch;
   bool hh_eta_JMSUp_isLoaded;
   float hh_eta_JMSDown_;
   TBranch *hh_eta_JMSDown_branch;
   bool hh_eta_JMSDown_isLoaded;
   float hh_eta_JMRUp_;
   TBranch *hh_eta_JMRUp_branch;
   bool hh_eta_JMRUp_isLoaded;
   float hh_eta_JMRDown_;
   TBranch *hh_eta_JMRDown_branch;
   bool hh_eta_JMRDown_isLoaded;
   float hh_mass_JESUp_;
   TBranch *hh_mass_JESUp_branch;
   bool hh_mass_JESUp_isLoaded;
   float hh_mass_JESDown_;
   TBranch *hh_mass_JESDown_branch;
   bool hh_mass_JESDown_isLoaded;
   float hh_mass_JMSUp_;
   TBranch *hh_mass_JMSUp_branch;
   bool hh_mass_JMSUp_isLoaded;
   float hh_mass_JMSDown_;
   TBranch *hh_mass_JMSDown_branch;
   bool hh_mass_JMSDown_isLoaded;
   float hh_mass_JMRUp_;
   TBranch *hh_mass_JMRUp_branch;
   bool hh_mass_JMRUp_isLoaded;
   float hh_mass_JMRDown_;
   TBranch *hh_mass_JMRDown_branch;
   bool hh_mass_JMRDown_isLoaded;
   float fatJet1PtOverMHH_;
   TBranch *fatJet1PtOverMHH_branch;
   bool fatJet1PtOverMHH_isLoaded;
   float fatJet1PtOverMHH_JESUp_;
   TBranch *fatJet1PtOverMHH_JESUp_branch;
   bool fatJet1PtOverMHH_JESUp_isLoaded;
   float fatJet1PtOverMHH_JESDown_;
   TBranch *fatJet1PtOverMHH_JESDown_branch;
   bool fatJet1PtOverMHH_JESDown_isLoaded;
   float fatJet1PtOverMHH_JMSUp_;
   TBranch *fatJet1PtOverMHH_JMSUp_branch;
   bool fatJet1PtOverMHH_JMSUp_isLoaded;
   float fatJet1PtOverMHH_JMSDown_;
   TBranch *fatJet1PtOverMHH_JMSDown_branch;
   bool fatJet1PtOverMHH_JMSDown_isLoaded;
   float fatJet1PtOverMHH_JMRUp_;
   TBranch *fatJet1PtOverMHH_JMRUp_branch;
   bool fatJet1PtOverMHH_JMRUp_isLoaded;
   float fatJet1PtOverMHH_JMRDown_;
   TBranch *fatJet1PtOverMHH_JMRDown_branch;
   bool fatJet1PtOverMHH_JMRDown_isLoaded;
   float fatJet1PtOverMSD_;
   TBranch *fatJet1PtOverMSD_branch;
   bool fatJet1PtOverMSD_isLoaded;
   float fatJet2PtOverMHH_;
   TBranch *fatJet2PtOverMHH_branch;
   bool fatJet2PtOverMHH_isLoaded;
   float fatJet2PtOverMHH_JESUp_;
   TBranch *fatJet2PtOverMHH_JESUp_branch;
   bool fatJet2PtOverMHH_JESUp_isLoaded;
   float fatJet2PtOverMHH_JESDown_;
   TBranch *fatJet2PtOverMHH_JESDown_branch;
   bool fatJet2PtOverMHH_JESDown_isLoaded;
   float fatJet2PtOverMHH_JMSUp_;
   TBranch *fatJet2PtOverMHH_JMSUp_branch;
   bool fatJet2PtOverMHH_JMSUp_isLoaded;
   float fatJet2PtOverMHH_JMSDown_;
   TBranch *fatJet2PtOverMHH_JMSDown_branch;
   bool fatJet2PtOverMHH_JMSDown_isLoaded;
   float fatJet2PtOverMHH_JMRUp_;
   TBranch *fatJet2PtOverMHH_JMRUp_branch;
   bool fatJet2PtOverMHH_JMRUp_isLoaded;
   float fatJet2PtOverMHH_JMRDown_;
   TBranch *fatJet2PtOverMHH_JMRDown_branch;
   bool fatJet2PtOverMHH_JMRDown_isLoaded;
   float fatJet2PtOverMSD_;
   TBranch *fatJet2PtOverMSD_branch;
   bool fatJet2PtOverMSD_isLoaded;
   float deltaEta_j1j2_;
   TBranch *deltaEta_j1j2_branch;
   bool deltaEta_j1j2_isLoaded;
   float deltaPhi_j1j2_;
   TBranch *deltaPhi_j1j2_branch;
   bool deltaPhi_j1j2_isLoaded;
   float deltaR_j1j2_;
   TBranch *deltaR_j1j2_branch;
   bool deltaR_j1j2_isLoaded;
   float ptj2_over_ptj1_;
   TBranch *ptj2_over_ptj1_branch;
   bool ptj2_over_ptj1_isLoaded;
   float mj2_over_mj1_;
   TBranch *mj2_over_mj1_branch;
   bool mj2_over_mj1_isLoaded;
   float lep1Pt_;
   TBranch *lep1Pt_branch;
   bool lep1Pt_isLoaded;
   float lep1Eta_;
   TBranch *lep1Eta_branch;
   bool lep1Eta_isLoaded;
   float lep1Phi_;
   TBranch *lep1Phi_branch;
   bool lep1Phi_isLoaded;
   int lep1Id_;
   TBranch *lep1Id_branch;
   bool lep1Id_isLoaded;
   float lep2Pt_;
   TBranch *lep2Pt_branch;
   bool lep2Pt_isLoaded;
   float lep2Eta_;
   TBranch *lep2Eta_branch;
   bool lep2Eta_isLoaded;
   float lep2Phi_;
   TBranch *lep2Phi_branch;
   bool lep2Phi_isLoaded;
   int lep2Id_;
   TBranch *lep2Id_branch;
   bool lep2Id_isLoaded;
   int nBTaggedJets_;
   TBranch *nBTaggedJets_branch;
   bool nBTaggedJets_isLoaded;
   bool HLT_Ele27_WPTight_Gsf_;
   TBranch *HLT_Ele27_WPTight_Gsf_branch;
   bool HLT_Ele27_WPTight_Gsf_isLoaded;
   bool HLT_Ele28_WPTight_Gsf_;
   TBranch *HLT_Ele28_WPTight_Gsf_branch;
   bool HLT_Ele28_WPTight_Gsf_isLoaded;
   bool HLT_Ele30_WPTight_Gsf_;
   TBranch *HLT_Ele30_WPTight_Gsf_branch;
   bool HLT_Ele30_WPTight_Gsf_isLoaded;
   bool HLT_Ele32_WPTight_Gsf_;
   TBranch *HLT_Ele32_WPTight_Gsf_branch;
   bool HLT_Ele32_WPTight_Gsf_isLoaded;
   bool HLT_Ele35_WPTight_Gsf_;
   TBranch *HLT_Ele35_WPTight_Gsf_branch;
   bool HLT_Ele35_WPTight_Gsf_isLoaded;
   bool HLT_Ele38_WPTight_Gsf_;
   TBranch *HLT_Ele38_WPTight_Gsf_branch;
   bool HLT_Ele38_WPTight_Gsf_isLoaded;
   bool HLT_Ele40_WPTight_Gsf_;
   TBranch *HLT_Ele40_WPTight_Gsf_branch;
   bool HLT_Ele40_WPTight_Gsf_isLoaded;
   bool HLT_IsoMu20_;
   TBranch *HLT_IsoMu20_branch;
   bool HLT_IsoMu20_isLoaded;
   bool HLT_IsoMu24_;
   TBranch *HLT_IsoMu24_branch;
   bool HLT_IsoMu24_isLoaded;
   bool HLT_IsoMu24_eta2p1_;
   TBranch *HLT_IsoMu24_eta2p1_branch;
   bool HLT_IsoMu24_eta2p1_isLoaded;
   bool HLT_IsoMu27_;
   TBranch *HLT_IsoMu27_branch;
   bool HLT_IsoMu27_isLoaded;
   bool HLT_IsoMu30_;
   TBranch *HLT_IsoMu30_branch;
   bool HLT_IsoMu30_isLoaded;
   bool HLT_Mu50_;
   TBranch *HLT_Mu50_branch;
   bool HLT_Mu50_isLoaded;
   bool HLT_Mu55_;
   TBranch *HLT_Mu55_branch;
   bool HLT_Mu55_isLoaded;
   bool HLT_Photon175_;
   TBranch *HLT_Photon175_branch;
   bool HLT_Photon175_isLoaded;
   bool HLT_PFHT780_;
   TBranch *HLT_PFHT780_branch;
   bool HLT_PFHT780_isLoaded;
   bool HLT_PFHT890_;
   TBranch *HLT_PFHT890_branch;
   bool HLT_PFHT890_isLoaded;
   bool HLT_PFHT1050_;
   TBranch *HLT_PFHT1050_branch;
   bool HLT_PFHT1050_isLoaded;
   bool HLT_AK8PFJet360_TrimMass30_;
   TBranch *HLT_AK8PFJet360_TrimMass30_branch;
   bool HLT_AK8PFJet360_TrimMass30_isLoaded;
   bool HLT_AK8PFJet380_TrimMass30_;
   TBranch *HLT_AK8PFJet380_TrimMass30_branch;
   bool HLT_AK8PFJet380_TrimMass30_isLoaded;
   bool HLT_AK8PFJet400_TrimMass30_;
   TBranch *HLT_AK8PFJet400_TrimMass30_branch;
   bool HLT_AK8PFJet400_TrimMass30_isLoaded;
   bool HLT_AK8PFJet420_TrimMass30_;
   TBranch *HLT_AK8PFJet420_TrimMass30_branch;
   bool HLT_AK8PFJet420_TrimMass30_isLoaded;
   bool HLT_AK8PFHT750_TrimMass50_;
   TBranch *HLT_AK8PFHT750_TrimMass50_branch;
   bool HLT_AK8PFHT750_TrimMass50_isLoaded;
   bool HLT_AK8PFHT800_TrimMass50_;
   TBranch *HLT_AK8PFHT800_TrimMass50_branch;
   bool HLT_AK8PFHT800_TrimMass50_isLoaded;
   bool HLT_AK8PFHT850_TrimMass50_;
   TBranch *HLT_AK8PFHT850_TrimMass50_branch;
   bool HLT_AK8PFHT850_TrimMass50_isLoaded;
   bool HLT_AK8PFHT900_TrimMass50_;
   TBranch *HLT_AK8PFHT900_TrimMass50_branch;
   bool HLT_AK8PFHT900_TrimMass50_isLoaded;
   bool HLT_PFJet450_;
   TBranch *HLT_PFJet450_branch;
   bool HLT_PFJet450_isLoaded;
   bool HLT_PFJet500_;
   TBranch *HLT_PFJet500_branch;
   bool HLT_PFJet500_isLoaded;
   bool HLT_PFJet550_;
   TBranch *HLT_PFJet550_branch;
   bool HLT_PFJet550_isLoaded;
   bool HLT_AK8PFJet400_;
   TBranch *HLT_AK8PFJet400_branch;
   bool HLT_AK8PFJet400_isLoaded;
   bool HLT_AK8PFJet450_;
   TBranch *HLT_AK8PFJet450_branch;
   bool HLT_AK8PFJet450_isLoaded;
   bool HLT_AK8PFJet500_;
   TBranch *HLT_AK8PFJet500_branch;
   bool HLT_AK8PFJet500_isLoaded;
   bool HLT_AK8PFJet550_;
   TBranch *HLT_AK8PFJet550_branch;
   bool HLT_AK8PFJet550_isLoaded;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_;
   TBranch *HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_isLoaded;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_;
   TBranch *HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_isLoaded;
   bool HLT_AK8PFJet330_PFAK8BTagCSV_p17_;
   TBranch *HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch;
   bool HLT_AK8PFJet330_PFAK8BTagCSV_p17_isLoaded;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_;
   TBranch *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_branch;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_isLoaded;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_;
   TBranch *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_branch;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_isLoaded;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_;
   TBranch *HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_branch;
   bool HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_isLoaded;
   bool HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_;
   TBranch *HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_branch;
   bool HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_isLoaded;
   bool HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_;
   TBranch *HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_branch;
   bool HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_isLoaded;
   bool HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_;
   TBranch *HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_branch;
   bool HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_isLoaded;
   bool HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_;
   TBranch *HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_branch;
   bool HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_isLoaded;
   bool HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_;
   TBranch *HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_branch;
   bool HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_isLoaded;
   bool HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_;
   TBranch *HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_branch;
   bool HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_isLoaded;
   float disc_qcd_and_ttbar_Run2_enhanced_v8p2_;
   TBranch *disc_qcd_and_ttbar_Run2_enhanced_v8p2_branch;
   bool disc_qcd_and_ttbar_Run2_enhanced_v8p2_isLoaded;
   float disc_qcd_and_ttbar_Run2_enhanced_v8p2_JESUp_;
   TBranch *disc_qcd_and_ttbar_Run2_enhanced_v8p2_JESUp_branch;
   bool disc_qcd_and_ttbar_Run2_enhanced_v8p2_JESUp_isLoaded;
   float disc_qcd_and_ttbar_Run2_enhanced_v8p2_JESDown_;
   TBranch *disc_qcd_and_ttbar_Run2_enhanced_v8p2_JESDown_branch;
   bool disc_qcd_and_ttbar_Run2_enhanced_v8p2_JESDown_isLoaded;
   float disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMSUp_;
   TBranch *disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMSUp_branch;
   bool disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMSUp_isLoaded;
   float disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMSDown_;
   TBranch *disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMSDown_branch;
   bool disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMSDown_isLoaded;
   float disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMRUp_;
   TBranch *disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMRUp_branch;
   bool disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMRUp_isLoaded;
   float disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMRDown_;
   TBranch *disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMRDown_branch;
   bool disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMRDown_isLoaded;
 
 
 public:
   void Init(TTree * tree);
   void GetEntry(unsigned int idx);
   void LoadAllBranches();
   const float &weight();
   const float &genMTT();
   const float &triggerEffWeight();
   const float &triggerEff3DWeight();
   const float &triggerEffMCWeight();
   const float &triggerEffMC3DWeight();
   const float &pileupWeight();
   const float &pileupWeightUp();
   const float &pileupWeightDown();
   const float &totalWeight();
   const unsigned int &run();
   const unsigned int &lumi();
   const unsigned long int &event();
   const float &npu();
   const float &rho();
   const int &NJets();
   const float &MET();
   const float &fatJet1Pt();
   const float &fatJet1Pt_JES_Up();
   const float &fatJet1Pt_JES_Down();
   const float &fatJet1Eta();
   const float &fatJet1Phi();
   const float &fatJet1Mass();
   const float &fatJet1MassSD();
   const float &fatJet1MassSD_UnCorrected();
   const float &fatJet1MassSD_JMS_Up();
   const float &fatJet1MassSD_JMS_Down();
   const float &fatJet1MassSD_JMR_Up();
   const float &fatJet1MassSD_JMR_Down();
   const float &fatJet1DDBTagger();
   const float &fatJet1PNetXbb();
   const float &fatJet1PNetQCDb();
   const float &fatJet1PNetQCDbb();
   const float &fatJet1PNetQCDc();
   const float &fatJet1PNetQCDcc();
   const float &fatJet1PNetQCDothers();
   const float &fatJet1_deepTagMD_W();
   const float &fatJet1_deepTagMD_Z();
   const float &fatJet1_deepTag_W();
   const float &fatJet1_deepTag_Z();
   const int &fatJet1GenMatchIndex();
   const float &fatJet1Tau3OverTau2();
   const float &fatJet1_n2b1();
   const bool &fatJet1HasMuon();
   const bool &fatJet1HasElectron();
   const bool &fatJet1HasBJetCSVLoose();
   const bool &fatJet1HasBJetCSVMedium();
   const bool &fatJet1HasBJetCSVTight();
   const bool &fatJet1OppositeHemisphereHasBJet();
   const int &isVBFtag();
   const float &dijetmass();
   const float &vbfjet1Pt();
   const float &vbfjet1Eta();
   const float &vbfjet1Phi();
   const float &vbfjet1Mass();
   const float &vbfjet2Pt();
   const float &vbfjet2Eta();
   const float &vbfjet2Phi();
   const float &vbfjet2Mass();
   const float &vbffatJet1PNetXbb();
   const float &vbffatJet1Pt();
   const float &vbffatJet1Eta();
   const float &vbffatJet1Phi();
   const float &vbffatJet2PNetXbb();
   const float &vbffatJet2Pt();
   const float &vbffatJet2Eta();
   const float &vbffatJet2Phi();
   const float &genHiggs1Pt();
   const float &genHiggs1Eta();
   const float &genHiggs1Phi();
   const float &genHiggs2Pt();
   const float &genHiggs2Eta();
   const float &genHiggs2Phi();
   const float &genHH_pt();
   const float &genHH_eta();
   const float &genHH_phi();
   const float &genHH_mass();
   const int &genLeptonId();
   const int &genLeptonMotherId();
   const float &genLeptonPt();
   const float &genLeptonEta();
   const float &genLeptonPhi();
   const float &fatJet2Pt();
   const float &fatJet2Pt_JES_Up();
   const float &fatJet2Pt_JES_Down();
   const float &fatJet2Eta();
   const float &fatJet2Phi();
   const float &fatJet2Mass();
   const float &fatJet2MassSD();
   const float &fatJet2MassSD_UnCorrected();
   const float &fatJet2MassSD_JMS_Up();
   const float &fatJet2MassSD_JMS_Down();
   const float &fatJet2MassSD_JMR_Up();
   const float &fatJet2MassSD_JMR_Down();
   const float &fatJet2DDBTagger();
   const float &fatJet2PNetXbb();
   const float &fatJet2PNetQCDb();
   const float &fatJet2PNetQCDbb();
   const float &fatJet2PNetQCDc();
   const float &fatJet2PNetQCDcc();
   const float &fatJet2PNetQCDothers();
   const float &fatJet2_deepTagMD_W();
   const float &fatJet2_deepTagMD_Z();
   const float &fatJet2_deepTag_W();
   const float &fatJet2_deepTag_Z();
   const int &fatJet2GenMatchIndex();
   const float &fatJet2Tau3OverTau2();
   const bool &fatJet2HasMuon();
   const bool &fatJet2HasElectron();
   const bool &fatJet2HasBJetCSVLoose();
   const bool &fatJet2HasBJetCSVMedium();
   const bool &fatJet2HasBJetCSVTight();
   const float &fatJet3Pt();
   const float &fatJet3Eta();
   const float &fatJet3Phi();
   const float &fatJet3Mass();
   const float &fatJet3MassSD();
   const float &fatJet3DDBTagger();
   const float &fatJet3PNetXbb();
   const float &fatJet3PNetQCDb();
   const float &fatJet3PNetQCDbb();
   const float &fatJet3PNetQCDc();
   const float &fatJet3PNetQCDcc();
   const float &fatJet3PNetQCDothers();
   const float &fatJet3Tau3OverTau2();
   const bool &fatJet3HasMuon();
   const bool &fatJet3HasElectron();
   const bool &fatJet3HasBJetCSVLoose();
   const bool &fatJet3HasBJetCSVMedium();
   const bool &fatJet3HasBJetCSVTight();
   const float &hh_pt();
   const float &hh_eta();
   const float &hh_phi();
   const float &hh_mass();
   const float &hh_pt_JESUp();
   const float &hh_pt_JESDown();
   const float &hh_pt_JMSUp();
   const float &hh_pt_JMSDown();
   const float &hh_pt_JMRUp();
   const float &hh_pt_JMRDown();
   const float &hh_eta_JESUp();
   const float &hh_eta_JESDown();
   const float &hh_eta_JMSUp();
   const float &hh_eta_JMSDown();
   const float &hh_eta_JMRUp();
   const float &hh_eta_JMRDown();
   const float &hh_mass_JESUp();
   const float &hh_mass_JESDown();
   const float &hh_mass_JMSUp();
   const float &hh_mass_JMSDown();
   const float &hh_mass_JMRUp();
   const float &hh_mass_JMRDown();
   const float &fatJet1PtOverMHH();
   const float &fatJet1PtOverMHH_JESUp();
   const float &fatJet1PtOverMHH_JESDown();
   const float &fatJet1PtOverMHH_JMSUp();
   const float &fatJet1PtOverMHH_JMSDown();
   const float &fatJet1PtOverMHH_JMRUp();
   const float &fatJet1PtOverMHH_JMRDown();
   const float &fatJet1PtOverMSD();
   const float &fatJet2PtOverMHH();
   const float &fatJet2PtOverMHH_JESUp();
   const float &fatJet2PtOverMHH_JESDown();
   const float &fatJet2PtOverMHH_JMSUp();
   const float &fatJet2PtOverMHH_JMSDown();
   const float &fatJet2PtOverMHH_JMRUp();
   const float &fatJet2PtOverMHH_JMRDown();
   const float &fatJet2PtOverMSD();
   const float &deltaEta_j1j2();
   const float &deltaPhi_j1j2();
   const float &deltaR_j1j2();
   const float &ptj2_over_ptj1();
   const float &mj2_over_mj1();
   const float &lep1Pt();
   const float &lep1Eta();
   const float &lep1Phi();
   const int &lep1Id();
   const float &lep2Pt();
   const float &lep2Eta();
   const float &lep2Phi();
   const int &lep2Id();
   const int &nBTaggedJets();
   const bool &HLT_Ele27_WPTight_Gsf();
   const bool &HLT_Ele28_WPTight_Gsf();
   const bool &HLT_Ele30_WPTight_Gsf();
   const bool &HLT_Ele32_WPTight_Gsf();
   const bool &HLT_Ele35_WPTight_Gsf();
   const bool &HLT_Ele38_WPTight_Gsf();
   const bool &HLT_Ele40_WPTight_Gsf();
   const bool &HLT_IsoMu20();
   const bool &HLT_IsoMu24();
   const bool &HLT_IsoMu24_eta2p1();
   const bool &HLT_IsoMu27();
   const bool &HLT_IsoMu30();
   const bool &HLT_Mu50();
   const bool &HLT_Mu55();
   const bool &HLT_Photon175();
   const bool &HLT_PFHT780();
   const bool &HLT_PFHT890();
   const bool &HLT_PFHT1050();
   const bool &HLT_AK8PFJet360_TrimMass30();
   const bool &HLT_AK8PFJet380_TrimMass30();
   const bool &HLT_AK8PFJet400_TrimMass30();
   const bool &HLT_AK8PFJet420_TrimMass30();
   const bool &HLT_AK8PFHT750_TrimMass50();
   const bool &HLT_AK8PFHT800_TrimMass50();
   const bool &HLT_AK8PFHT850_TrimMass50();
   const bool &HLT_AK8PFHT900_TrimMass50();
   const bool &HLT_PFJet450();
   const bool &HLT_PFJet500();
   const bool &HLT_PFJet550();
   const bool &HLT_AK8PFJet400();
   const bool &HLT_AK8PFJet450();
   const bool &HLT_AK8PFJet500();
   const bool &HLT_AK8PFJet550();
   const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17();
   const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1();
   const bool &HLT_AK8PFJet330_PFAK8BTagCSV_p17();
   const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02();
   const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2();
   const bool &HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4();
   const bool &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20();
   const bool &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087();
   const bool &HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087();
   const bool &HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20();
   const bool &HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20();
   const bool &HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20();
   const float &disc_qcd_and_ttbar_Run2_enhanced_v8p2();
   const float &disc_qcd_and_ttbar_Run2_enhanced_v8p2_JESUp();
   const float &disc_qcd_and_ttbar_Run2_enhanced_v8p2_JESDown();
   const float &disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMSUp();
   const float &disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMSDown();
   const float &disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMRUp();
   const float &disc_qcd_and_ttbar_Run2_enhanced_v8p2_JMRDown();
};   

#ifndef __CINT__   
extern hhtree hh;   
#endif   

#endif   
