#pragma once

#include "TObject.h"

class Hit {
  float edep_;
  std::vector<float> position_;
 public:
  void setEDep(float edep);
  float getEDep() const;
  void setPosition(const std::vector<float>& position);
  std::vector<float> getPosition() const;
  ClassDef(Hit, 1);
};
