#pragma once
#include "TObject.h"
#include <string>
#include <map>

namespace v2 {

class Header {
  int run_number_;
  int event_number_;
 public:
  void setRun(int run);
  int getRun() const;
  void setEvent(int event);
  int getEvent() const;
  ClassDef(Header, 2);
};

}
