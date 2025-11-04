#ifdef __CINT__

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#pragma link C++ class Header+ ;

#pragma read \
  sourceClass="Header" \
  source="int runNumber_;" \
  version="[-5]" \
  targetClass="Header" \
  target="run_number_, my_parameters_, myParameters_" \
  include="iostream" \
  code="{ std::cout << \"'both' schema evolution rule being applied: run_number_ = onfile.runNumber_; my_parameters_ = myParameters_;\" << std::endl; run_number_ = onfile.runNumber_; my_parameters_ = myParameters_; }"

#endif
