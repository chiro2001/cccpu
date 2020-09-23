#include "../../include/includes.h"
#include "../../include/units.h"

class ALF {
 public:
  REG *reg;
  ALF(REG *p) : reg(p) {}
  virtual void execute(WORD) = 0;
};