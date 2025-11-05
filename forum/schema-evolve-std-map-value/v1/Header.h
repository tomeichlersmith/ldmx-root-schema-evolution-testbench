#pragma once

#include "TObject.h"
#include <string>
#include <map>

class Header {
  int runNumber_;
  int eventNumber_;
 public:
  void setRun(int run);
  int getRun() const;
  void setEvent(int event);
  int getEvent() const;
  ClassDef(Header, 1);
};
