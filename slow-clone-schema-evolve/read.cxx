#include <iostream>

#include "TFile.h"
#include "TTreeReader.h"

#include "Header.h"
#include "Hit.h"

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
  TTreeReaderValue<std::vector<Hit>> hits(tree, "hits");
  TTreeReaderValue<std::vector<Header>> headers(tree, "headers");
  TTreeReaderValue<std::map<int, Header>> header_map(tree, "header_map");
  std::size_t i{0};
  while (tree.Next()) {
    auto header_ptr = header.Get();
    int run = header_ptr->getRun();
    int event = header_ptr->getEvent();
    std::cout << "header: { run: " << run << ", event: " << event << " } tenindex: " << *tenindex << std::endl;
    std::cout << "hits: {";
    for (const auto& hit : *(hits.Get())) {
      std::cout << " [ " << hit.getEDep() << " (";
      for (const auto& x : hit.getPosition()) {
        std::cout << " " << x;
      }
      std::cout << " ) ]";
    }
    std::cout << " }" << std::endl;
    std::cout << "headers: [";
    for (const auto& h : *(headers.Get())) {
      std::cout << " { run: " << h.getRun() << ", event: " << h.getEvent() << "}";
    }
    std::cout << " ]" << std::endl;
    std::cout << "header_map: {";
    for (const auto& [i, h] : *(header_map.Get())) {
      std::cout << " " << i << ": { run: " << h.getRun() << ", event: " << h.getEvent() << "}";
    }
    std::cout << " }" << std::endl;
    i++;
  }
  return 0;
}
