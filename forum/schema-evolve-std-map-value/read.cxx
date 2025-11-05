#include <iostream>

#include "TFile.h"
#include "TTreeReader.h"

#include "Header.h"
#include "output.h"

int main(int nargs, char** argv) {
  TFile f{FILENAME};
  TTreeReader tree("tree", &f);
  TTreeReaderValue<std::map<int, Header>> header_map(tree, "header_map");
  while (tree.Next()) {
    std::cout << "header_map: {";
    for (const auto& [i, h] : *(header_map.Get())) {
      std::cout << " " << i << ": { run: " << h.getRun() << ", event: " << h.getEvent() << "}";
    }
    std::cout << " }" << std::endl;
  }
  return 0;
}
