// 节拍发生器
#include "incs.h"

class CLK {
 public:
  // class Pack {
  //   public:
  //   ALF* task = NULL;
  //   WORD data
  // };
  std::vector<ALF*> tasks;
  const u32 clock_time = CLOCK_TIME;
  const u32 clock_frequency = CLOCK_FREQUENCY;
  REG *pc = NULL, *ir = NULL;
  STD* _std = NULL;

  CLK(STD* istd) : _std(istd) {}

  CLK(REG* ipc, REG* iir, STD* istd) : pc(ipc), ir(iir), _std(istd) {}
  void add_task(ALF* target) {}
  void execute_all() {
    for (auto task : this->tasks) {
      // task->execute();
    }
  }
  void loop() {
    while (true) {
      // 发送地址等待指令
      this->_std->str.set(this->pc->data);
      // 等待储存取出
      this->_std->execute();
      Sleep(this->clock_time);
      // 取出指令到控制器
      this->ir->set(this->_std->stc.data);
    }
  }
};

// using namespace std;
// // 测试时钟
// int main() {
//   cout << "测试时钟" << endl;
//   double start, stop, durationTime;
//   start = clock();

//   // Sleep(5 * 1000);  //程序延时5s
//   Sleep(CLOCK_TIME);  //程序延时5ms
//   stop = clock();
//   durationTime = ((double)(stop - start)) / CLOCKS_PER_SEC;
//   cout << "总耗时：" << durationTime << "s" << endl;

//   cout << "sizeof(ALF) = " << sizeof(ALF) << endl
//        << "sizeof(XAD) = " << sizeof(XAD) << endl;

//   XAD xad = XAD(new REG(32));
//   cout << "data1 = " << xad.reg->data << endl;
//   // // xad.execute(123);
//   // ALF *alf = (ALF*) &xad;
//   // alf->execute(123);
//   // cout << "data1 = " << xad.reg->data << endl;
//   // cout << "data2 = " << alf->reg->data << endl;

//   // vector<ALF *> vec;
//   // vec.push_back((ALF *)&xad);
//   // ALF *front = vec.front();
//   // cout << "front = " << front << endl;
//   // XAD *judge1 = dynamic_cast<XAD *>(front);
//   // cout << "judge1 = " << judge1 << endl;
//   // XMT *judge2 = dynamic_cast<XMT *>(front);
//   // cout << "judge2 = " << judge2 << endl;

//   // front->execute(123);
//   // cout << "data1 = " << front->reg->data << endl;

//   // vec.pop_back();

//   // XMT xmt = XMT(new REG(4));
//   // vec.push_back((ALF *)&xmt);
//   // front = vec.front();
//   // cout << "front = " << front << endl;
//   // cout << "data2 = " << front->reg->data << endl;
//   // judge1 = dynamic_cast<XAD *>(front);
//   // cout << "judge1 = " << judge1 << endl;
//   // judge2 = dynamic_cast<XMT *>(front);
//   // cout << "judge2 = " << judge2 << endl;

//   // front->execute(3);
//   // cout << "data2 = " << front->reg->data << endl;

//   vector<ALF *> vec;
//   vec.push_back((ALF *)new XAD(new REG(1)));
//   vec.push_back((ALF *)new XMT(new REG(2)));

//   for (auto val : vec) {
//     val->execute(3);
//   }

//   for (auto val : vec) {
//     cout << "data = " << val->reg->data << endl;
//   }

//   return 0;
// }
