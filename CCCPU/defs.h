//------------------------------
//
// 预处理的各种定义
//
//------------------------------

// 类型定义
#define u4 unsigned char
#define u8 unsigned short int
#define u16 unsigned int
#define u32 unsigned long long int
#define u64 unsigned long double

// 数据长度定义
constexpr auto WORD_SIZE = 8;

// 单字节
#define WORD u8
// 双字节
#define DWORD u16
// 四字节
#define QWORD u64
// 取高低字节
#define WORDH(x) ((x & 0xF0) >> 4)
#define WORDL(x) (x & 0x0F)

// 运行时参数
// 时钟频率 单位HZ
//#define CLOCK_FREQUENCY 1000 * 1000 * 1000		// 最快110kHz
constexpr auto CLOCK_FREQUENCY = 10;
#define CLOCK_TIME (int)((double)(1) * 1000 / (double)(CLOCK_FREQUENCY))

constexpr auto PROGRAME_START = 0x0000;
constexpr auto MEMORY_SIZE = 0x8000;		//32768 WORDS

constexpr auto FILE_MEMORY = "D:\\Programs\\cccpu\\memory.txt";

#ifndef NULL
#define NULL 0
#endif