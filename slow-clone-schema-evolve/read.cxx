#include <iostream>

#include "TFile.h"
#include "TTreeReader.h"

#ifdef AS_OLD
#include "v1/Header.h"
#else
#include "v2/Header.h"
using namespace v2;
#endif

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
    i++;
  }
  return 0;
}
