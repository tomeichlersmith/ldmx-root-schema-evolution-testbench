#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "Header.h"
#include "Hit.h"

int main(int nargs, char** argv) {
  if (nargs < 2) {
    std::cerr << "ERROR: Need to provide output file\n";
    return 1;
  } else if (nargs > 2) {
    std::cerr << "WARN : Only using first two arguments, the rest are ignored\n"
      << "      " << argv[1] << " (output file)\n"
      << "      " << argv[2] << " (presence indicates to create a second branch)"
      << std::endl;
  }
  TFile f{argv[1], "recreate"};
  TTree t{"tree", "tree"};
  std::vector<Hit> hits;
  Header h;
  int i10;
  h.setRun(42);
  t.Branch("hits", &hits);
  t.Branch("header", &h);
  t.Branch("tenindex", &i10);
  for (std::size_t i{0}; i < 10; i++) {
    hits.clear();
    for (std::size_t i_hit{0}; i_hit < (10-i)/2; i_hit++) {
      hits.emplace_back();
      float hit{0.5f*static_cast<float>(i_hit)};
      hits.back().setEDep(hit);
      hits.back().setPosition({hit-0.25f, hit, hit+0.25f});
    }
    i10 = 10*i;
    h.setEvent(i);
    t.Fill();
  }
  f.Write();
  return 0;
}
