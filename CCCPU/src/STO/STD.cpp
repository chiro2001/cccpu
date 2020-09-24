#include "incs.h"

class STD : public DAT {
 public:
  STC stc;
  STR str;
  STD(u32 size) : DAT(size) {}
  void set_str(WORD addr) { this->str.set(addr); }
  void execute() { this->stc.set(this->get_dat(this->str.get())); }
  WORD get_stc() { return this->stc.get(); }
};
