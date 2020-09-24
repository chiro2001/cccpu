#include "incs.h"

using namespace std;
int main() {
  STD _std(1024);
  CTL ctl = CTL(&_std);
  ctl.loop();
}
