//------------------------------
//
// 预处理的各种定义
//
//------------------------------

// 类型定义
#define u4 unsigned char
#define u8 unsigned short
#define u16 unsigned int
#define u32 unsigned long long int
#define u64 unsigned long double

// 数据长度定义
#define WORD_SIZE 8

// 单字节
#define WORD u8
// 双字节
#define DWORD u16
// 四字节
#define QWORD u64

// 运行时参数
// 时钟频率 单位HZ
#define CLOCK_FREQUENCY 5
#define CLOCK_TIME (int)((double)(1) * 1000 / (double)(CLOCK_FREQUENCY))

#define PROGRAME_START 0x0000

#define FILE_MEMORY "D:\\Programs\\cccpu\\CCCPU\\memory.txt"