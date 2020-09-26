#include <Windows.h>

//#include <boost/regex.hpp>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <map>
#include <bitset>
#include <csignal>
#include <stdarg.h>


#include "defs.h"

//class REG;
//class CLK;
//class ALF;
//class DAT;
//class STD;
//class XAD;
//class XMT;
//class CTL;

//#define STC REG
//#define STR REG
//#define ADD REG
//#define MLT REG
//#define COM REG
//#define PC REG
//#define IR REG


void cccpu_stop();
void cccpu_restart();
void cccpu_controller();
void cccpu_parser();
void cccpu_clock();

void print_log(u8);

enum {
	LOG_TEXT = 0x06,
	LOG_DEBUG = 0x07,
	LOG_INFO = 0x0A,
	LOG_WARNING = 0x0E,
	LOG_ERROR = 0x0C,
	LOG_CRITICAL = 0x0D,
};
