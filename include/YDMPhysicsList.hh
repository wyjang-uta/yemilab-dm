#ifndef YDMPhysicsList_h
#define YDMPhysicsList_h

#include "YDMDetectorConstruction.hh"
#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include <vector>

class G4PhysicsConstructor;
class YDMDetectorConstruction;

class YDMPhysicsList: public G4VModularPhysicsList
{
  public:
    YDMPhysicsList(YDMDetectorConstruction* det);
    virtual ~YDMPhysicsList();
    void ConstructProcess();

  private:
    G4String              fEmName;
    G4VPhysicsConstructor*  fEmPhysicsList;
    G4VPhysicsConstructor*  fDecPhysicsList;
    G4VPhysicsConstructor*  fHadPhysicsList;
    G4VPhysicsConstructor*  fRaddecayList;

    YDMDetectorConstruction* fDetector;
};

#endif
