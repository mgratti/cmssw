#include "ECALPFSeedCleaner.h"
//#include "CondFormats/EcalObjects/interface/EcalPFRecHitThresholds.h"
//#include "CondFormats/DataRecord/interface/EcalPFRecHitThresholdsRcd.h"

#include <cmath>

ECALPFSeedCleaner::ECALPFSeedCleaner(const edm::ParameterSet& conf) 
    : RecHitTopologicalCleanerBase(conf)
{
//  eventSetup_ = nullptr;
}

void ECALPFSeedCleaner::update(const edm::EventSetup& iSetup) {
  std::cout << "DEBUG ECALPFSeedCleaner::update" << std::endl;
  //eventSetup_ = &iSetup;
  //(*eventSetup_).get<EcalPFRecHitThresholdsRcd>().get(ths);
  iSetup.get<EcalPFSeedingThresholdsRcd>().get(ths_);
  std::cout << "DEBUG ECALPFSeedCleaner::update 2" << std::endl;
}

void ECALPFSeedCleaner::clean(const edm::Handle<reco::PFRecHitCollection>& input, std::vector<bool>& mask ) {

  //std::cout << "DEBUG ECALPFSeedCleaner::clean" << std::endl;
  // Get thresholds from record
  //edm::ESHandle<EcalPFRecHitThresholds> ths;
  std::cout << "DEBUG ECALPFSeedCleaner::clean 1" << std::endl;
  //(*eventSetup_).get<EcalPFRecHitThresholdsRcd>().get(ths);

  //need to run over energy sorted rechits
  // this can cause ambiguity, isn't it better to index by detid ?
  auto const & hits = *input;
  std::vector<unsigned > ordered_hits(hits.size());
  for( unsigned i = 0; i < hits.size(); ++i ) ordered_hits[i]=i;
  std::sort(ordered_hits.begin(),ordered_hits.end(),[&](unsigned i, unsigned j) { return hits[i].energy()>hits[j].energy();});
  std::cout << "DEBUG ECALPFSeedCleaner::clean 2" << std::endl;

  for( const auto& idx : ordered_hits ) {
    const unsigned i = idx;
    if( !mask[i] ) continue; // surplus ?
    const reco::PFRecHit& rechit = hits[i];
    //int hitlayer = (int)rechit.layer();

    // put selection on thrs here
    //const spike_cleaning& clean = _thresholds.find(hitlayer)->second;    
    //if( rechit.energy() < clean._singleSpikeThresh ) continue;

    float threshold = (*ths_)[rechit.detId()];
    std::cout << "DEBUG ECALPFSeedCleaner::clean 3" << std::endl;
    if (rechit.energy() < threshold) mask[i] = false;
    
    std::cout << "DEBUG seed cleaner " << " hit energy=" << rechit.energy() << " hit threshold=" << threshold << " mask=" << mask[i] << std::endl;

  } // rechit loop
}
