#include "Pythia8/Pythia.h"
#include "TTree.h"
#include "TFile.h"

int getMult() {
  gSystem->Load("qcdGen.so");
  TFile *file = TFile::Open("qcd.root");
  Pythia8::Event *event;
  TTree *tree = (TTree*)file->Get("tree");
  tree->SetBranchAddress("event",&event);

  // Begin event loop.
  int nEvent = tree->GetEntriesFast();
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    tree->GetEntry(iEvent);
    int nP = event->size();
    int mult = 0;
    for (int iP = 0; iP < nP; ++iP) {
      Pythia8::Particle p = event->at(iP);
      if (p.isFinal() && p.isCharged()) {
        mult++;
      }
    }
    std::cout << mult << "\n";
  }

  return 0;
}
