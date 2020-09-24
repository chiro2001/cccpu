#include "incs.h"
// #include "../../include/incs.h"

class CTL {
 public:
  REG pc, ir;
  CLK* clk;
  STD* _std = NULL;
  CTL(STD* istd) : _std(istd), pc(REG(PROGRAME_START)), ir(REG()) {
    this->clk = new CLK(&(this->pc), &(this->ir), this->_std);
  }
  void loop() { this->clk->loop(); }
};
