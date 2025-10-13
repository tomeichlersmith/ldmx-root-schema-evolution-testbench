#include "TFile.h"
#include "TTreeReader.h"

#ifdef USE_HEADER_V2
#include "Header_v2.h"
#else
#include "Header_v1.h"
#endif

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
#ifdef USE_HEADER_V2
    std::cout << "my_parameter[example]: ";
#else
    std::cout << "myParameter[example]: ";
#endif
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
