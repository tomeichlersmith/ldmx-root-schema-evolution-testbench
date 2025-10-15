#include <iostream>

#include "TFile.h"
#include "TTreeReader.h"

#include "Header.h"

int main(int nargs, char** argv) {
  std::string branch{"header"};
  if (nargs < 2) {
    std::cout << "ERROR: Need to provide file to read.\n";
    return 1;
  } else if (nargs == 3) {
    branch = argv[2];
  } else if (nargs > 4) {
    std::cout << "ERROR: Too many command line arguments.\n";
    return 2;
  }
  TFile f{argv[1]};
  TTreeReader tree("tree", &f);
  TTreeReaderValue<Header> header(tree, branch.c_str());
  std::size_t i{0};
  while (tree.Next()) {
    auto header_ptr = header.Get();
    int run = header_ptr->getRun();
    int event = header_ptr->getEvent();
    std::cout << "{ run: " << run << ", event: " << event << " }" << std::endl;
    if (run != 42) {
      std::cout << "  run != 42" << std::endl;
    }
    if (i != event) {
      std::cout << "  event != index" << std::endl;
    }
    i++;
  }
  return 0;
}
