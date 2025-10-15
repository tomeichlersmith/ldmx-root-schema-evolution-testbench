#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "Header.h"

int main(int nargs, char** argv) {
  bool second_branch{false};
  if (nargs < 2) {
    std::cerr << "ERROR: Need to provide output file\n";
    return 1;
  } else if (nargs == 3) {
    std::cout << "INFO : Will write a second 'header-cp' branch to copy without reading.\n";
    second_branch = true;
  } else if (nargs > 4) {
    std::cerr << "WARN : Only using first two arguments, the rest are ignored\n"
      << "      " << argv[1] << " (output file)\n"
      << "      " << argv[2] << " (presence indicates to create a second branch)"
      << std::endl;
  }
  TFile f{argv[1], "recreate"};
  TTree t{"tree", "tree"};
  Header h;
  h.setRun(42);
  t.Branch("header", &h);
  if (second_branch) {
    t.Branch("header-cp", &h);
  }
  for (std::size_t i{0}; i < 10; i++) {
    h.setEvent(i);
    t.Fill();
  }
  f.Write();
  return 0;
}
