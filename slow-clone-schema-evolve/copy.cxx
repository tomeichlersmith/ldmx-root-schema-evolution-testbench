#include "TFile.h"
#include "TTreeReader.h"

#ifdef USE_HEADER_V2
#include "Header_v2.h"
#define FILEPREF "v2-copy-"
#else
#include "Header_v1.h"
#define FILEPREF "v1-copy-"
#endif

int main(int nargs, char** argv) {
  std::string input_file{argv[1]};
  TFile f{input_file.c_str()};
  TTree* input_tree{(TTree*)f.Get("tree")};
  TFile o{(FILEPREF+input_file).c_str(), "recreate"};
  TTree* output_tree = input_tree->CloneTree(0);

  Header* h_ptr = new Header;
  input_tree->SetBranchAddress("header", &h_ptr);
  for (std::size_t i{0}; i < input_tree->GetEntriesFast(); i++) {
    input_tree->GetEntry(i);
    int run = h_ptr->getRun();
    int event = h_ptr->getEvent();
    std::cout << "{ run: " << run << ", event: " << event << " }" << std::endl;
    if (run != 42) {
      std::cout << "  run != 42" << std::endl;
    }
    if (i != event) {
      std::cout << "  event != index" << std::endl;
    }

    output_tree->Fill();
  }

  delete h_ptr;
  output_tree->Write();

  return 0;
}
