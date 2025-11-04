#include "Header.h"
#include <iostream>

ClassImp(Header);

void Header::setRun(int run) {
  run_number_ = run;
}

int Header::getRun() const {
  return run_number_;
}

void Header::add(const std::string& name, int val) {
  my_parameters_[name] = val;
}

int Header::get(const std::string& name) const {
  return my_parameters_.at(name);
}

void Header::print() const {
  std::cout << "{ " << "run_number_ = " << run_number_ << ", my_parameters_ = { ";
  for (const auto& [key, val]: my_parameters_) {
    std::cout << key << ": " << val << " ";
  }
  std::cout << "} }" << std::endl;
}
