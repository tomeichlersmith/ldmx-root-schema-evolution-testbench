#include <iostream>

#include "TFile.h"
#include "TTreeReader.h"

#include "Header.h"

int main(int nargs, char** argv) {
  if (nargs < 3) {
    std::cout << "ERROR: Need to provide an input file to readout and output file to write to.\n";
    return 1;
  } else if (nargs > 3) {
    std::cout << "WARN : Only using first two arguments for input and output file respectively.\n";
  }
  std::string input_file{argv[1]};
  TFile f{argv[1]};
  TTree* input_tree{f.Get<TTree>("tree")};
  TFile o{argv[2], "recreate"};

#ifdef USE_TTREE_CLONETREE
  /**
   * Cloning the Tree without the addresses is not working.
   */
  Header* h_ptr = nullptr; //new Header;
  input_tree->SetBranchAddress("header", &h_ptr);
  TTree* output_tree = input_tree->CloneTree(0);
  output_tree->SetBranchAddress("header", &h_ptr);
#elif MANUAL_ADDR_SYNC
  /**
   * "Cloning" the Tree manually by constructing a new Tree
   * and creating the branches directly does appear to work
   */
  Header* h_ptr = nullptr; //new Header;
  input_tree->SetBranchAddress("header", &h_ptr);
  TTree* output_tree = new TTree("tree", "tree");
  output_tree->Branch("header", &h_ptr);
#else
  /**
   * Solution as described by @pcanal on ROOT Forum.
   */
  TTree* output_tree = new TTree("tree", "tree");
  input_tree->GetEntry(0);
  input_tree->CopyAddresses(output_tree);
  Header* h_ptr = nullptr; //new Header;
  input_tree->SetBranchAddress("header", &h_ptr);
  output_tree->SetBranchAddress("header", &h_ptr);
#endif

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

  //output_tree->Write();

  o.Write();

  //delete h_ptr;
  //delete output_tree;

  return 0;
}
