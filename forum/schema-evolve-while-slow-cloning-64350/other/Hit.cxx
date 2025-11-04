#include "Hit.h"

ClassImp(Hit);

void Hit::setEDep(float edep) {
  edep_ = edep;
}

float Hit::getEDep() const {
  return edep_;
}

void Hit::setPosition(const std::vector<float>& position) {
  position_ = position;
}

std::vector<float> Hit::getPosition() const {
  return position_;
}
