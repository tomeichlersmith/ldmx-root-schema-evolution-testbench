#include "Header_v1.h"

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

