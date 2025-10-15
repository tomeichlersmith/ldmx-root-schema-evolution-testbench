#include "TFile.h"
#include "TTreeReader.h"

#ifdef USE_HEADER_V2
#include "Header_v2.h"
#else
#include "Header_v1.h"
#endif

int main(int nargs, char** argv) {
  TFile f{argv[1]};
  TTreeReader tree("tree", &f);
  TTreeReaderValue<Header> header(tree, "header");
  std::size_t i{0};
  while (tree.Next()) {
    auto header_ptr = header.Get();
    int run = header_ptr->getRun();
    int event = header_ptr->getEvent();
    std::cout << "{ run: " << run << ", event: " << event << " }" << std::endl;
    if (run != 42) {
      std::cout << "  run != 42" << std::endl;
      return 1;
    }
    if (i != event) {
      std::cout << "  event != index" << std::endl;
      return 2;
    }
    i++;
  }
  return 0;
}
