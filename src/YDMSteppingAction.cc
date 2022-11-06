//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file YDMSteppingAction.cc
/// \brief Implementation of the YDMSteppingAction class

#include "YDMSteppingAction.hh"
#include "YDMEventAction.hh"
#include "YDMDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4ParticleTypes.hh"
#include "G4PVPlacement.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YDMSteppingAction::YDMSteppingAction(YDMEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fTargetVolume(0),
  fWorldVolume(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

YDMSteppingAction::~YDMSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void YDMSteppingAction::UserSteppingAction(const G4Step* step)
{
  const YDMDetectorConstruction* detectorConstruction
    = static_cast<const YDMDetectorConstruction*>
      (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  fWorldVolume = detectorConstruction->GetWorldPV();

  // get volume of the current step
  /*
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      */

  auto analysisManager = G4AnalysisManager::Instance();

  const std::vector<const G4Track*>* secondary = step->GetSecondaryInCurrentStep();
  //G4StepPoint* preStep = step->GetPreStepPoint();
  for( size_t lp=0; lp < (*secondary).size(); lp++ )
  {
    analysisManager->FillNtupleSColumn(0, (*secondary)[lp]->GetCreatorProcess()->GetProcessName());
    analysisManager->FillNtupleDColumn(1, (G4double)(*secondary)[lp]->GetTotalEnergy()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(2, (G4double)(*secondary)[lp]->GetKineticEnergy()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(3, (G4double)(*secondary)[lp]->GetPosition().getX());
    analysisManager->FillNtupleDColumn(4, (G4double)(*secondary)[lp]->GetPosition().getY());
    analysisManager->FillNtupleDColumn(5, (G4double)(*secondary)[lp]->GetPosition().getZ());
    analysisManager->FillNtupleDColumn(6, (G4double)(*secondary)[lp]->GetMomentum().getX()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(7, (G4double)(*secondary)[lp]->GetMomentum().getY()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(8, (G4double)(*secondary)[lp]->GetMomentum().getZ()/CLHEP::MeV);
    analysisManager->FillNtupleDColumn(9, (G4double)(*secondary)[lp]->GetMomentumDirection().getX());
    analysisManager->FillNtupleDColumn(10, (G4double)(*secondary)[lp]->GetMomentumDirection().getY());
    analysisManager->FillNtupleDColumn(11, (G4double)(*secondary)[lp]->GetMomentumDirection().getZ());
    analysisManager->FillNtupleSColumn(12, (*secondary)[lp]->GetDefinition()->GetParticleName() );
    analysisManager->FillNtupleSColumn(13, step->GetTrack()->GetParticleDefinition()->GetParticleName());
    analysisManager->AddNtupleRow();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

