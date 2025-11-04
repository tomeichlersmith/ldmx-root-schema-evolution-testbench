#include "Header.h"
#include <iostream>

ClassImp(Header);

void Header::setRun(int run) {
  runNumber_ = run;
}

int Header::getRun() const {
  return runNumber_;
}

void Header::add(const std::string& name, int val) {
  myParameters_[name] = val;
}

int Header::get(const std::string& name) const {
  return myParameters_.at(name);
}

void Header::print() const {
  std::cout << "{ " << "runNumber_ = " << runNumber_ << ", myParameters_ = { ";
  for (const auto& [key, val]: myParameters_) {
    std::cout << key << ": " << val << " ";
  }
  std::cout << "} }" << std::endl;
}
