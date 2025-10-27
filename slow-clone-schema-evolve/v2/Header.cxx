#include "Header.h"

ClassImp(v2::Header);

namespace v2 {

void Header::setRun(int run) {
  run_number_ = run;
}

int Header::getRun() const {
  return run_number_;
}

void Header::setEvent(int event) {
  event_number_ = event;
}

int Header::getEvent() const {
  return event_number_;
}

}
