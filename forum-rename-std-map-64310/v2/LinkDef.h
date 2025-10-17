#ifdef __CINT__

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#pragma link C++ class Header+ ;

#pragma read \
  sourceClass="Header" \
  source="int runNumber_; std::map<std::string, int> myParameters_;" \
  version="[-5]" \
  targetClass="Header" \
  target="run_number_, my_parameters_" \
  include="iostream" \
  code="{ std::cout << \"v2 schema evolution rule being applied: run_number_ = onfile.runNumber_; my_parameters_ = onfile.myParameters_;\" << std::endl; run_number_ = onfile.runNumber_; my_parameters_ = onfile.myParameters_; }"

#endif
