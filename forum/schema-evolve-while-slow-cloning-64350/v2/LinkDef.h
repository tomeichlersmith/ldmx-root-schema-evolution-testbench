#ifdef __CINT__

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#pragma link C++ class Header+ ;
#pragma link C++ class std::vector<Header>+;
#pragma link C++ class std::map<int, Header>+;

#pragma read \
  sourceClass="Header" \
  source="int runNumber_; int eventNumber_;" \
  version="[-5]" \
  targetClass="Header" \
  target="run_number_, event_number_" \
  include="iostream" \
  code="{ run_number_ = onfile.runNumber_; event_number_ = onfile.eventNumber_; }"

#endif
