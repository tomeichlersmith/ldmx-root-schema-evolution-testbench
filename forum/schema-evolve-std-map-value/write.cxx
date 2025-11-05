#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "Header.h"
#include "output.h"

int main(int nargs, char** argv) {
  TFile f{FILENAME, "recreate"};
  TTree t{"tree", "tree"};
  std::map<int, Header> header_map;
  t.Branch("header_map", &header_map);
  for (std::size_t i{0}; i < 10; i++) {
    header_map.clear();
    header_map[i].setRun(42);
    header_map[i].setEvent(i*10);
    t.Fill();
  }
  f.Write();
  return 0;
}
