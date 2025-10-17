#include "TFile.h"
#include "TTreeReader.h"

#include "Header.h"

int main() {
  TFile f{"v1-output.root"};
  TTreeReader tree("tree", &f);
  TTreeReaderValue<Header> header(tree, "header");
  while (tree.Next()) {
    auto header_ptr = header.Get();
    header_ptr->print();
    int run = header_ptr->getRun();
    if (run != 2) {
      return 1;
    }
    int eg{-1};
    try {
      eg = header_ptr->get("example");
    } catch (const std::out_of_range& e) {
      return 2;
    }
    if (eg != 42) {
      return 3;
    }
  }
  return 0;
}
