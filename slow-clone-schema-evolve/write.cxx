#include "TFile.h"
#include "TTree.h"

#ifdef USE_HEADER_V2
#define FILENAME "v2-output.root"
#include "Header_v2.h"
#else
#define FILENAME "v1-output.root"
#include "Header_v1.h"
#endif

int main() {
  TFile f{FILENAME, "recreate"};
  TTree t{"tree", "tree"};
  Header h;
  h.setRun(42);
  t.Branch("header", &h);
  for (std::size_t i{0}; i < 10; i++) {
    h.setEvent(i);
    t.Fill();
  }
  f.Write();
  return 0;
}
