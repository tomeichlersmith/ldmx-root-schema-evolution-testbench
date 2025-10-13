#include "TFile.h"
#include "TTree.h"
#include "Header_v1.h"

int main() {
  TFile f{"v1-output.root", "recreate"};
  TTree t{"tree", "tree"};
  Header h;
  h.setRun(2);
  h.add("example", 42);
  t.Branch("header", &h);
  t.Fill();
  f.Write();
  return 0;
}
