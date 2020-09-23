#include "../../include/includes.h"

class DAT {
 public:
  WORD *data = NULL;
  u32 size = 0;
  DAT(u32 size) {
    this->data = new WORD[size];
    this->size = size;
  }
  ~DAT() { delete this->data; }
  bool set_dat(WORD addr, WORD dat) {
    if (dat > this->size || this->data == NULL) return false;
    this->data[addr] = dat;
    return true;
  }
  WORD get_dat(WORD addr) {
    if (addr > this->size || this->data == NULL) return NULL;
    return this->data[addr];
  }
};