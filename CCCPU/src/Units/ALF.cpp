#include "incs.h"

#ifndef USE_ALF
class ALF {
 public:
  REG *reg;
  ALF(REG *p) : reg(p) {}
  // void execute(WORD);
  virtual void execute(WORD) = 0;
  // virtual void execute(WORD a) {}
};
#endif