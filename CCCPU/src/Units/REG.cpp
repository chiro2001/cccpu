#include "../../include/includes.h"

class REG {
 public:
  WORD data = 0;
  REG(WORD src) : data(src) {}
  REG() : data(0) {}
  REG operator+(const REG &a) { return REG(this->data + a.data); }
  REG operator+(const WORD &a) { return REG(this->data + a); }
  void operator+=(const REG &a) { this->data += a.data; }
  void operator+=(const WORD &a) { this->data += a; }
  REG operator*(const REG &a) { return REG(this->data * a.data); }
  REG operator*(const WORD &a) { return REG(this->data * a); }
  void operator*=(const REG &a) { this->data *= a.data; }
  void operator*=(const WORD &a) { this->data *= a; }
  void set(WORD d) { this->data = d; }
  WORD get() { return this->data; }
};
