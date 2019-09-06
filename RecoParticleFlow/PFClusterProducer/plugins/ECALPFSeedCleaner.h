#ifndef __ECALPFSeedCleaner_H__
#define __ECALPFSeedCleaner_H__

#include "RecoParticleFlow/PFClusterProducer/interface/RecHitTopologicalCleanerBase.h"
#include "CondFormats/EcalObjects/interface/EcalPFSeedingThresholds.h"
#include "CondFormats/DataRecord/interface/EcalPFSeedingThresholdsRcd.h"
//#include <unordered_map>

class ECALPFSeedCleaner : public RecHitTopologicalCleanerBase {
 public:
  
  ECALPFSeedCleaner(const edm::ParameterSet& conf);
  ECALPFSeedCleaner(const ECALPFSeedCleaner&) = delete;
  ECALPFSeedCleaner& operator=(const ECALPFSeedCleaner&) = delete;

  void update(const edm::EventSetup&) override;

  void clean( const edm::Handle<reco::PFRecHitCollection>& input,
	      std::vector<bool>& mask ) override;

  //const edm::EventSetup* eventSetup_;

 private:
  //const std::unordered_map<std::string,int> _layerMap;
  //std::unordered_map<int,spike_cleaning> _thresholds;
  edm::ESHandle<EcalPFSeedingThresholds> ths_; 
};

DEFINE_EDM_PLUGIN(RecHitTopologicalCleanerFactory,
		  ECALPFSeedCleaner,"ECALPFSeedCleaner");

#endif
