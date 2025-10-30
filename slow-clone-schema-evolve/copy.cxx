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

  input_tree->GetEntry(0);

  /* fine, i'll write my own CloneTree
   */
  TTree* output_tree = new TTree("tree","tree");
  auto input_branches = input_tree->GetListOfBranches();
  for (std::size_t i_br{0}; i_br < input_branches->GetEntriesFast(); i_br++) {
    auto br{dynamic_cast<TBranchElement*>(input_branches->UncheckedAt(i_br))};

    // check if copying
    // e.g. with GetBranchStatus

    output_tree->Branch(br->GetName(), br->GetClassName(), br->GetObject());
  }

  output_tree->Print();

  /* using CloneTree
  TTree* output_tree = input_tree->CloneTree(0);
  */

  Header* h_ptr = nullptr; //new Header;
  input_tree->SetBranchAddress("header", &h_ptr);
  output_tree->SetBranchAddress("header", &h_ptr);

  /* unset kDeleteObject
  auto input_br = input_tree->GetBranch("header");
  // TBranchElement::EStatusBits::kDeleteObject
  // is protected so I manually copy the index
  input_br->SetBit((1ULL << (16)), false);
  input_br->SetObject(h_ptr);

  auto output_br = output_tree->GetBranch("header");
  output_br->SetBit((1ULL << (16)), false);
  dynamic_cast<TBranchElement*>(output_br)->ResetDeleteObject();
  output_br->SetObject(h_ptr);
  */

  for (std::size_t i{0}; i < input_tree->GetEntriesFast(); i++) {
    input_tree->GetEntry(i);

    int run = h_ptr->getRun();
    int event = h_ptr->getEvent();
    std::cout << "{ run: " << run << ", event: " << event << " }" << std::endl;
    output_tree->Fill();
  }
  output_tree->Write();
  o.Write();

  //delete h_ptr;
  //delete output_tree;

  return 0;
}
