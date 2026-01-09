#include <iostream>

#include "TFile.h"
#include "TTreeReader.h"

#include "Header.h"
#include "output.h"

int main(int nargs, char** argv) {
  TFile f{FILENAME};
  auto tree = f.Get<TTree>("tree");
  std::map<int, Header> header_map;
  tree->GetBranch("header_map")->SetObject(&header_map);
  for (int i_entry{0}; i_entry < tree->GetEntriesFast(); i_entry++) {
    tree->GetEntry(i_entry);
    std::cout << "header_map: {";
    for (const auto& [i, h] : header_map) {
      std::cout << " " << i << ": { run: " << h.getRun() << ", event: " << h.getEvent() << "}";
    }
    std::cout << " }" << std::endl;
  }
  return 0;
}
