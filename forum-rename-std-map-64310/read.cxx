#include "TFile.h"
#include "TTreeReader.h"

#include "Header.h"

int main() {
  TFile f{"v1-output.root"};
  TTreeReader tree("tree", &f);
  TTreeReaderValue<Header> header(tree, "header");
  while (tree.Next()) {
    auto header_ptr = header.Get();
    int run = header_ptr->getRun();
    std::cout << "run: " << run << std::endl;
    if (run != 2) {
      return 1;
    }
    std::cout << "my parameter[example]: ";
    int eg{-1};
    try {
      eg = header_ptr->get("example");
    } catch (const std::out_of_range& e) {
      std::cout << "does not exist" << std::endl;
      return 2;
    }
    std::cout << eg << std::endl;
    if (eg != 42) {
      return 3;
    }
  }
  return 0;
}
