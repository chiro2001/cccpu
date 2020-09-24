#include "incs.h"

#ifndef USE_DAT
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
    if (addr > this->size || this->data == NULL) return 0;
    return this->data[addr];
  }

  bool readfile(char *filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    std::string line;
    while (getline(file, line)) {
      std::cout << line << std::endl;
      // 先删除注释内容
      std::regex cm1("/\*.+?\*/");
    }
    return true;
  }
};
#endif
#ifndef USE_MAIN
int main() {
  DAT dat = DAT(1024);
  dat.readfile(FILE_MEMORY);
  return 0;
}
#endif