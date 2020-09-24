// 加法操作

#include "incs.h"

class XAD : public ALF {
 public:
  XAD(REG *reg): ALF(reg) {}
  virtual void execute(WORD arg) {
    *(this->reg) += arg;
  }
};
