#include "Header.h"

#ifdef AS_OLD
ClassImp(Header);
#else
ClassImp(v1::Header);
namespace v1 {
#endif

void Header::setRun(int run) {
  runNumber_ = run;
}

int Header::getRun() const {
  return runNumber_;
}

void Header::setEvent(int event) {
  eventNumber_ = event;
}

int Header::getEvent() const {
  return eventNumber_;
}

#ifndef AS_OLD
}
#endif
