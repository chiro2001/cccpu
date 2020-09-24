// 乘法操作

#include "incs.h"


class XMT : public ALF {
 public:
  XMT(REG *reg): ALF(reg) {}
  void execute(WORD arg) {
    *(this->reg) *= arg;
  }
};
