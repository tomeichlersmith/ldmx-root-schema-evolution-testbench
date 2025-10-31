#include <iostream>
#include <dlfcn.h>

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

  void *handle = dlopen("build/libHit.so", RTLD_NOW);

  std::string input_file{argv[1]};
  TFile f{argv[1]};
  TTree* input_tree{f.Get<TTree>("tree")};
  TFile o{argv[2], "recreate"};

  input_tree->GetEntry(0);
  input_tree->Print();

  /* fine, i'll write my own CloneTree
   */
  TTree* output_tree = new TTree("tree","tree");
  auto input_branches = input_tree->GetListOfBranches();
  for (std::size_t i_br{0}; i_br < input_branches->GetEntriesFast(); i_br++) {
    auto br{dynamic_cast<TBranch*>(input_branches->UncheckedAt(i_br))};

    // check if copying
    // e.g. with GetBranchStatus
   
    if (auto bre{dynamic_cast<TBranchElement*>(br)}; bre) {
      // anything more complex than a simple BSIFLD fundamental type
      // this fails if the in-memory dictionary of classes does not contain
      // the object we are trying to copy over. In this case, we want to fallback
      // to directly copying the leaves because in this situation (without a dictionary),
      // there are certainly no schema rules to apply (they only come with a dictionary)
      auto br = output_tree->Branch(
          bre->GetName(),
          bre->GetClassName(),
          bre->GetObject()
      );
      if (!br) {
        // cloning branches that don't have a dictionary should be possible
        // (its what CloneTree does)
        // but I can't figure it out and its easier to just require
        // there to be a dictionary
        std::cout << "no dictionary-entry for class '" << bre->GetClassName()
          << "' written to '" << bre->GetName()
          << "', fall-back option of leaf-based address syncing not implemented since we want to evolve the schema" << std::endl;
        continue;
        // I tried this but it seg-vio
        output_tree->GetListOfBranches()->Add(bre->Clone());
      }
    } else {
      // br->GetClassName() -> nullptr
      // br->GetFullName() == br->GetName() since this is assumed to be a root branch
      // br->GetTypeName() not implemented for TBranch
      // br->GetAddress() -> nullptr (i expected this to be the same as leaf->GetValuePointer())
      // leaf->GetValuePointer() -> whats used in TTree::CopyAddresses
      auto leaf{br->GetLeaf(br->GetName())};
      /*
      std::cout << "Simple Type : {"
        << " br->name: " << br->GetName()
        << " br->type: " << br->GetClassName()
        << " br->addr: " << static_cast<void*>(br->GetAddress())
        << " lf->type: " << leaf->GetTypeName()
        << " lf->addr: " << leaf->GetValuePointer()
        << " }" << std::endl;
        */
      static const std::map<std::string, std::string> TYPENAME_TO_LEAFLIST = {
        { "Int_t", "I" }
        // TODO: add rest of BSILFD options
      };
      std::string leaflist{br->GetName()};
      auto leaf_type_name{leaf->GetTypeName()};
      leaflist += "/" + TYPENAME_TO_LEAFLIST.at(br->GetLeaf(br->GetName())->GetTypeName());
      output_tree->Branch(
          br->GetName(),
          leaf->GetValuePointer(),
          leaflist.c_str()
      );
    }
  }

  /* using CloneTree
   * we could try to CloneTree and then remove branches but
   * that seems to be more work than just always including the dictionary
   * and when I tried the naive approach, it segfaulted after the first event
  TTree* output_tree = input_tree->CloneTree(0);
  input_tree->GetListOfClones()->Remove(output_tree);
  // get and remove branch pointing at input address
  auto output_br = output_tree->GetBranch("header");
  output_tree->GetListOfBranches()->Remove(output_br);
  // create new branch (same name) with new address
  output_br = output_tree->Branch("header", &h_ptr);
  */

  Header* h_ptr = nullptr;

  output_tree->SetBranchAddress("header", &h_ptr);
  input_tree->SetBranchAddress("header", &h_ptr);

  output_tree->Print();

  for (std::size_t i{0}; i < input_tree->GetEntriesFast(); i++) {
    input_tree->GetEntry(i);

    int run = h_ptr->getRun();
    int event = h_ptr->getEvent();
    std::cout << "{ run: " << run << ", event: " << event << " }" << std::endl;
    output_tree->Fill();
  }
  output_tree->Write();
  o.Write();

  delete h_ptr;
  delete output_tree;

  return 0;
}
