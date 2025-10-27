#ifdef __CINT__

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#ifdef AS_OLD
#pragma link C++ class Header+;
#else
#pragma link C++ namespace v1;
#pragma link C++ class v1::Header+;
#endif

#endif
