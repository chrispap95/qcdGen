// QCD generator
// Using main03.cc and main92.cc as baseline code

#include "Pythia8/Pythia.h"
#include "TTree.h"
#include "TFile.h"

using namespace Pythia8;

int main(int argc, char **argv) {

  // Generator.
  Pythia pythia;

  // Shorthand for the event record in pythia.
  //Event& event = pythia.event;

  // Read in commands from external file.
  pythia.readFile(argv[1]);

  // Extract settings to be used in the main program.
  int nEvent = pythia.mode("Main:numberOfEvents");
  int nAbort = pythia.mode("Main:timesAllowErrors");

  // Initialize.
  pythia.init();

  // Set up the ROOT TFile and TTree.
  TFile *file = TFile::Open(argv[2],"recreate");
  Event *event = &pythia.event;
  TTree *tree = new TTree("tree","tree");
  int nTracks;
  tree->Branch("nTracks",&nTracks);

  // Begin event loop.
  int iAbort = 0;
  int nFilter = 0;
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {

    // Generate events. Quit if many failures.
    if (!pythia.next()) {
      if (++iAbort < nAbort) continue;
      cout << " Event generation aborted prematurely, owing to error!\n";
      break;
    }

    int nP = event->size();
    nTracks = 0;
    double genHT = 0;
    for (int iP = 0; iP < nP; ++iP) {
      Particle p = event->at(iP);
      int pid = p.id();
      Particle mom1 = event->at(p.mother1());
      Particle mom2 = event->at(p.mother2());
      int mom1id = abs(mom1.id());
      int mom2id = abs(mom2.id());

      if (p.isFinal()) {
        genHT += p.pT();
      }

      if (p.isFinal() && p.isCharged() && abs(p.eta())<2.5 && p.pT()>1) {
        nTracks++;
      }
    }

    if (genHT > 1200) {
      tree->Fill();
      nFilter++;
    }
  // End of event loop.
  }

  std::cout << "Accepted " << nFilter << " events out of " << nEvent << std::endl;

  // Final statistics. Normalize and output histograms.
  pythia.stat();
  tree->Write();
  delete file;

  // Done.
  return 0;
}
