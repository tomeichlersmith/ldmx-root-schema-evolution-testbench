#ifdef __CINT__

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#pragma link C++ class Header+;

#pragma link C++ namespace v1;
#pragma link C++ class v1::Header+;

#pragma link C++ namespace v2;
#pragma link C++ class v2::Header+;

//#pragma read sourceClass="Header" version="[-1]" targetClass="v1::Header"
#pragma read \
  sourceClass="Header" \
  version="[-1]" \
  source="int runNumber_; int eventNumber_;" \
  targetClass="v2::Header" \
  target="run_number_, event_number_" \
  code="{ run_number_ = onfile.runNumber_; event_number_ = onfile.eventNumber_; }"

#endif
