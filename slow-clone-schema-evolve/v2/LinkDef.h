#ifdef __CINT__

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#pragma link C++ class Header+ ;

#pragma read \
  sourceClass="Header" \
  source="int runNumber_; int eventNumber_;" \
  version="[-5]" \
  targetClass="Header" \
  target="run_number_, event_number_" \
  include="iostream" \
  code="{ std::cout << \"manual schema evolution rule being applied\" << std::endl; run_number_ = onfile.runNumber_; event_number_ = onfile.eventNumber_; }"

#endif
