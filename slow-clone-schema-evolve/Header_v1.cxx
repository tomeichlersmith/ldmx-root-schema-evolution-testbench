#include "Header_v1.h"

ClassImp(Header);

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

