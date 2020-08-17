#include <ostream>

#include "IOMC/ParticleGuns/interface/CloseByParticleMultiGunProducer.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "DataFormats/Math/interface/Vector3D.h"

#include <TMath.h>

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Units/GlobalSystemOfUnits.h"
#include "CLHEP/Units/GlobalPhysicalConstants.h"
#include "CLHEP/Random/RandFlat.h"

using namespace edm;
using namespace std;

CloseByParticleMultiGunProducer::CloseByParticleMultiGunProducer(const ParameterSet& pset) :
   BaseFlatGunProducer(pset)
{

  ParameterSet defpset ;
  ParameterSet pgun_params =
    pset.getParameter<ParameterSet>("PGunParameters") ;

  fdoFlatEnergy = pgun_params.getParameter<bool>("doFlatEnergy");
  fPtMin = pgun_params.getParameter<double>("MinPt");
  fPtMax = pgun_params.getParameter<double>("MaxPt");
  fRMax = pgun_params.getParameter<double>("RMax");
  fRMin = pgun_params.getParameter<double>("RMin");
  fZMax = pgun_params.getParameter<double>("ZMax");
  fZMin = pgun_params.getParameter<double>("ZMin");
  fDelta = pgun_params.getParameter<double>("Delta");
  fDeltaPhi = pgun_params.getParameter<double>("DeltaPhi");
  fPhiMin = pgun_params.getParameter<double>("MinPhi");
  fPhiMax = pgun_params.getParameter<double>("MaxPhi");
  fPointing = pgun_params.getParameter<bool>("Pointing");
  fOverlapping = pgun_params.getParameter<bool>("Overlapping");
  fRandomShoot = pgun_params.getParameter<bool>("RandomShoot");
  fNParticles = pgun_params.getParameter<int>("NParticles");
  fPartIDs = pgun_params.getParameter< vector<int> >("PartID");

  produces<HepMCProduct>("unsmeared");
  produces<GenEventInfoProduct>();

}

CloseByParticleMultiGunProducer::~CloseByParticleMultiGunProducer()
{
   // no need to cleanup GenEvent memory - done in HepMCProduct
}

void CloseByParticleMultiGunProducer::produce(Event &e, const EventSetup& es)
{
   edm::Service<edm::RandomNumberGenerator> rng;
   CLHEP::HepRandomEngine* engine = &rng->getEngine(e.streamID());

   if ( fVerbosity > 0 )
     {
       LogDebug("CloseByParticleMultiGunProducer") << " CloseByParticleMultiGunProducer : Begin New Event Generation" << endl ;
     }
   fEvt = new HepMC::GenEvent() ;

   // loop over particles
   //
   int barcode = 1 ;
   //int numParticles = fRandomShoot ? CLHEP::RandFlat::shoot(engine, 1, fNParticles) : fNParticles;
   int numParticles = fNParticles;
   std::vector<int> particles;

   for(int i=0; i<numParticles; i++){
     int partIdx = CLHEP::RandFlat::shoot(engine, 0, fPartIDs.size());
     particles.push_back(fPartIDs[partIdx]);
     }

   double phi = CLHEP::RandFlat::shoot(engine, fPhiMin, fPhiMax);
   double fR = CLHEP::RandFlat::shoot(engine,fRMin,fRMax);
   double fZ = CLHEP::RandFlat::shoot(engine,fZMin,fZMax); // EE+ or all EB

   for (unsigned int ip=0; ip<particles.size(); ++ip)
   {
     if(fOverlapping)
       {
         if(ip!=0) {
           // now add a randomised deltaZ and deltaPhi variation, interesting for EB only
           if(fRandomShoot){
             fZ += CLHEP::RandFlat::shoot(engine,0,fDelta);        
             phi += CLHEP::RandFlat::shoot(engine,0,fDeltaPhi);
           } else {
             fZ += fDelta;
             phi += fDeltaPhi;
           }
         }
       }
     else{
       phi += 2*TMath::Pi()/(float)numParticles; 
     }

     // if EE, generate one particle in EE+ and next particle in EE-
     if(fZMin==fZMax){
       fZ*=-1; // change at every round
     }

     double px=0,py=0,pz=0,mom=0,energy=0;
     int PartID = particles[ip];
     const HepPDT::ParticleData *PData = fPDGTable->particle(HepPDT::ParticleID(abs(PartID)));
     double mass = PData->mass().value();

     if(fdoFlatEnergy){ // generation flat in Energy
       double fEn = CLHEP::RandFlat::shoot(engine,fPtMin,fPtMax);
       mom    = sqrt(fEn*fEn-mass*mass);
       px     = 0.;
       py     = 0.;
       pz     = mom;
       energy = fEn;
     }else{ //generation flat in Et
       double pt = CLHEP::RandFlat::shoot(engine,fPtMin,fPtMax);
       double theta  = acos(fZ/sqrt(fR*fR + fZ*fZ)) ;
       mom    = pt/sin(theta) ;
       px     = pt*cos(phi) ;
       py     = pt*sin(phi) ;
       pz     = mom*cos(theta) ;
       double energy2= mom*mom + mass*mass ;
       energy = sqrt(energy2) ; 
     }

     // Compute Vertex Position
     double x=fR*cos(phi);
     double y=fR*sin(phi);
     constexpr double c= 2.99792458e+1; // cm/ns
     double timeOffset = sqrt(x*x + y*y + fZ*fZ)/c*ns*c_light;
     HepMC::GenVertex* Vtx = new HepMC::GenVertex(HepMC::FourVector(x*cm,y*cm,fZ*cm,timeOffset));

     HepMC::FourVector p(px,py,pz,energy) ;
     // If we are requested to be pointing to (0,0,0), correct the momentum direction
     if (fPointing) {
       math::XYZVector direction(x,y,fZ);
       math::XYZVector momentum = direction.unit() * mom;
       p.setX(momentum.x());
       p.setY(momentum.y());
       p.setZ(momentum.z());
     }
     HepMC::GenParticle* Part = new HepMC::GenParticle(p,PartID,1);
     Part->suggest_barcode( barcode );
     barcode++;

     Vtx->add_particle_out(Part);

     if (fVerbosity > 0) {
       Vtx->print();
       Part->print();
     }
     fEvt->add_vertex(Vtx);
   }


   fEvt->set_event_number(e.id().event());
   fEvt->set_signal_process_id(20);

   if ( fVerbosity > 0 )
   {
      fEvt->print();
   }

   unique_ptr<HepMCProduct> BProduct(new HepMCProduct());
   BProduct->addHepMCData( fEvt );
   e.put(std::move(BProduct), "unsmeared");

   unique_ptr<GenEventInfoProduct> genEventInfo(new GenEventInfoProduct(fEvt));
   e.put(std::move(genEventInfo));

   if ( fVerbosity > 0 )
     {
       LogDebug("CloseByParticleMultiGunProducer") << " CloseByParticleMultiGunProducer : Event Generation Done " << endl;
     }

   particles.clear();
}
