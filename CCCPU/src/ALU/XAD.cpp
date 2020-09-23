// 加法操作

#include "../../include/includes.h"
#include "../Units/ALF.cpp"
#include "./ADD.cpp"

class XAD : public ALF {
 public:
  XAD(REG *reg): ALF(reg) {}
  void execute(WORD arg) {
    this->reg += arg;
  }
};
