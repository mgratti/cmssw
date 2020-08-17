#ifndef IOMC_ParticleGun_CloseByParticleMultiGunProducer_H
#define IOMC_ParticleGun_CloseByParticleMultiGunProducer_H

#include "IOMC/ParticleGuns/interface/BaseFlatGunProducer.h"

namespace edm
{

  class CloseByParticleMultiGunProducer : public BaseFlatGunProducer
  {

  public:
    CloseByParticleMultiGunProducer(const ParameterSet &);
    ~CloseByParticleMultiGunProducer() override;

  private:

    void produce(Event & e, const EventSetup& es) override;

  protected :

    // data members
    double fPtMax,fPtMin,fRMin,fRMax,fZMin,fZMax,fPhiMin,fPhiMax;
    int fNParticles;
    bool fdoFlatEnergy = false;
    bool fPointing = false;
    bool fOverlapping = false;
    bool fRandomShoot = false;
    double fDelta = 2.2; // in cm 
    double fDeltaPhi = 0.01744; // one crystal in radiants
    std::vector<int> fPartIDs;
  };
}

#endif
