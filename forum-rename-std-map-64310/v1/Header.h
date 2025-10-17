#pragma once

#include "TObject.h"
#include <string>
#include <map>

class Header {
  int runNumber_;
  std::map<std::string, int> myParameters_;
 public:
  void setRun(int run);
  int getRun() const;
  void add(const std::string& name, int val);
  int get(const std::string& name) const;
  void print() const;
  ClassDef(Header, 5);
};
