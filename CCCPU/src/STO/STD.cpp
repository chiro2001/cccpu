#include "../../include/includes.h"
#include "../Units/DAT.cpp"
#include "./STC.cpp"
#include "./STR.cpp"

class STD : public DAT {
 public:
  STC stc;
  STR str;
  void set_str(WORD addr) { this->str.set(addr); }
  void excute() { this->stc.set(this->get_dat(this->str.get())); }
  WORD get_stc() { return this->stc.get(); }
};