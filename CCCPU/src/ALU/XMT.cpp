// 乘法操作

#include "../../include/includes.h"
#include "../Units/ALF.cpp"
#include "./MLT.cpp"

class XMT : public ALF {
 public:
  XMT(REG *reg): ALF(reg) {}
  void execute(WORD arg) {
    *(this->reg) *= arg;
  }
};
