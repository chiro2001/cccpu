// 节拍发生器
#include "../../include/includes.h"
#include "../ALU/XAD.cpp"

// class CLK {
//  public:
//  vector<ALF>
// };

using namespace std;
// 测试时钟
int main() {
  cout << "测试时钟" << endl;
  double start, stop, durationTime;
  start = clock();

  // Sleep(5 * 1000);  //程序延时5s
  Sleep(CLOCK_TIME);  //程序延时5ms
  stop = clock();
  durationTime = ((double)(stop - start)) / CLOCKS_PER_SEC;
  cout << "总耗时：" << durationTime << "s" << endl;

  cout << "sizeof(ALF) = " << sizeof(ALF) << endl << "sizeof(XAD) = " << sizeof(XAD) << endl;

  XAD xad = XAD(new REG());
  ALF alf = (ALF)xad;

  return 0;
}
