#include <iostream>

#include "TFile.h"
#include "TTreeReader.h"

#include "Header.h"

int main(int nargs, char** argv) {
  if (nargs < 2) {
    std::cout << "ERROR: Need to provide file to read.\n";
    return 1;
  } else if (nargs > 2) {
    std::cout << "ERROR: Too many command line arguments.\n";
    return 2;
  }
  TFile f{argv[1]};
  TTreeReader tree("tree", &f);
  TTreeReaderValue<Header> header(tree, "header");
  TTreeReaderValue<int> tenindex(tree, "tenindex");
  std::size_t i{0};
  while (tree.Next()) {
    auto header_ptr = header.Get();
    int run = header_ptr->getRun();
    int event = header_ptr->getEvent();
    std::cout << "header: { run: " << run << ", event: " << event << " } tenindex: " << *tenindex << std::endl;
    i++;
  }
  return 0;
}
