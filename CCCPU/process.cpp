#include "incs.h"

/*
全局变量的面向过程方案
ALF可以操作一切全局的资源
*/

class REG;
class DAT;

const u32 clock_time = CLOCK_TIME;
const u32 clock_frequency = CLOCK_FREQUENCY;
typedef void (*ALF)();
std::map<WORD, ALF> cccpu_table;
std::map<WORD, std::string> cccpu_table_str;
char buf[1024 * 2];
char buf_bin[1024 * 2];

bool running = true;

//const bool debugging = false;
const bool debugging = true;

void sig_handler(int sig)
{
	if (sig == SIGINT)
		running = false;
}

char* to_bin(u16 num) {
	_itoa_s(num, buf_bin, 1024, 2);
	return buf_bin;
}

WORD set_color(WORD color) {
	WORD colorOld;
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	colorOld = csbi.wAttributes;
	SetConsoleTextAttribute(handle, color);
	return colorOld;
}

class REG {
public:
	WORD data = 0;
	REG(WORD src) : data(src) {}
	REG() : data(0) {}

	void operator=(const REG& a) { this->data = a.data; }

	REG operator+(const REG& a) { return REG(this->data + a.data); }
	REG operator+(const WORD& a) { return REG(this->data + a); }
	void operator+=(const REG& a) { this->data += a.data; }
	void operator+=(const WORD& a) { this->data += a; }

	REG operator*(const REG& a) { return REG(this->data * a.data); }
	REG operator*(const WORD& a) { return REG(this->data * a); }
	void operator*=(const REG& a) { this->data *= a.data; }
	void operator*=(const WORD& a) { this->data *= a; }

	void set(WORD d) { this->data = d; }
	void set(REG& a) { this->data = a.data; }
	WORD get() { return this->data; }
}ADD, MLT, COM, PC, IR, STR, STC;

class DAT {
public:
	WORD* data = NULL;
	u32 size = 0;
	DAT(u32 size) {
		this->data = new WORD[size];
		this->size = size;
		for (u32 i = 0; i < size; i++)
			this->data[i] = 0;
	}
	~DAT() { delete this->data; }
	void clear() {
		if (this->size == 0 || this->data == NULL)
			return;
		memset(this->data, this->size, sizeof(WORD));
	}
	bool set_dat() {
		if (STR.get() > this->size || this->data == NULL) return false;
		this->data[STR.get()] = STC.get();
		return true;
	}
	WORD get_dat(WORD addr) {
		if (addr > this->size || this->data == NULL) return 0;
		return this->data[addr];
	}
	void execute() { STC.set(this->get_dat(STR.get())); }

	bool readfile(const char* filename) {
		std::ifstream file(filename);
		if (!file.is_open()) return false;
		std::string line;
		u16 pos = 0;
		while (getline(file, line)) {
			// 先删除注释内容
			std::regex cm1("/\\*.+?\\*/");
			// 先形成一个WORD
			WORD tmp = 0;
			std::string rline(line.rbegin(), line.rend());
			for (char i : line) {
				if (i != '1' && i != '0')
					continue;
				tmp <<= 1;
				if (i == '1')
					tmp |= 0x0001;
			}
			WORD cmd = WORDH(tmp);
			if (debugging && cccpu_table.find(cmd) != cccpu_table.end()) {
				sprintf_s(buf, "{%08s} => <%08s : 0x%02X>", to_bin(tmp), cccpu_table_str[cmd].c_str(), WORDL(tmp));
				print_log(LOG_DEBUG);
			}
			this->data[pos] = tmp;
			pos++;
		}
		return true;
	}
}STD(MEMORY_SIZE);

// 取数操作
void XNG() {
	WORD addr = WORDL(IR.get());
	STR.set(addr);
	STD.execute();
	cccpu_clock();
	COM.set(STC.get());
	if (debugging) {
		sprintf_s(buf, "<XNG>:%04s", to_bin(STC.get()));
		print_log(LOG_DEBUG);
	}
	cccpu_clock();
}

// 存数操作
void XNS() {
	STR.set(WORDL(IR.get()));
	STC.set(COM);
	cccpu_clock();
	STD.set_dat();
	cccpu_clock();
}

// 加法操作
void XAD() {
	ADD += COM;
	cccpu_clock();
}

// 乘法操作
void XMT() {
	MLT *= COM;
	cccpu_clock();
}

// 跳转到addr操作
void JMP() {
	WORD addr = WORDL(IR.get());
	PC.set(addr);
	cccpu_clock();
}

// 打印COM
void PRT() {
	sprintf_s(buf, "<PNT>:%s(0x%02X %d)", to_bin(COM.get()), COM.get(), COM.get());
	print_log(LOG_CRITICAL);
	cccpu_clock();
}

// 停机
void STP() {
	cccpu_stop();
}


u32 clock_cnt = 0;

void cccpu_clock() {
	Sleep(clock_time);
	clock_cnt++;
}

void cccpu_parser() {
	WORD cmd = WORDH(IR.get());
	if (cccpu_table.find(cmd) == cccpu_table.end())
		return;
	if (debugging) {
		sprintf_s(buf, "<%s>(%04s)", cccpu_table_str[cmd].c_str(), to_bin(cmd));
		print_log(LOG_INFO);
	}
	cccpu_table[cmd]();
}

// 控制器
void cccpu_controller() {
	while (running) {
		STR.set(PC);
		if (debugging) {
			sprintf_s(buf, "[%4d]{%08s}", PC.get(), to_bin(STD.data[PC.get()]));
			print_log(LOG_DEBUG);
		}
		// 等待储存器反应
		STD.execute();
		Sleep(clock_time);
		// 取出指令到指令寄存器
		IR.set(STC);
		// PC自增
		PC += 1;
		// 执行指令
		cccpu_parser();
		if (debugging)
			std::cout << std::endl;
	}
	if (!running)
		cccpu_stop();
}

clock_t sys_start;
clock_t sys_stop;

std::map<u8, std::string>log_map = {
	{LOG_TEXT, "TEXT"},
	{LOG_DEBUG, "DEBUG"},
	{LOG_INFO, "INFO"},
	{LOG_WARNING, "WARNING"},
	{LOG_ERROR, "ERROR"},
	{LOG_CRITICAL, "CRITICAL"},
};

void print_log(u8 level = LOG_TEXT) {
	WORD old = set_color(level);
	printf("[%10.3f][%10s]%s\n", (float)((double)clock() - (double)sys_start), log_map[level].c_str(), buf);
	set_color(old);
	buf[0] = 0;
}

// 开机
void cccpu_restart() {
	sys_start = clock();
	// 设置指令集
	cccpu_table[0x1] = XNG;				//0x01 取数字
	cccpu_table[0x2] = XNS;				//0x02 存数字
	cccpu_table[0x3] = XAD;				//0x03 加法
	cccpu_table[0x4] = XMT;				//0x04 乘法
	cccpu_table[0x5] = JMP;				//0x05 跳转
	cccpu_table[0x6] = PRT;				//0x06 打印
	cccpu_table[0xF] = STP;				//0xFF 停机

	cccpu_table_str[0x1] = "XNG";				//0x01 取数字
	cccpu_table_str[0x2] = "XNS";				//0x02 存数字
	cccpu_table_str[0x3] = "XAD";				//0x03 加法
	cccpu_table_str[0x4] = "XMT";				//0x04 乘法
	cccpu_table_str[0x5] = "JMP";				//0x05 跳转
	cccpu_table_str[0x6] = "PRT";				//0x06 打印
	cccpu_table_str[0xF] = "STP";				//0xFF 停机
	PC.set(PROGRAME_START);
	STD.clear();
	STD.readfile(FILE_MEMORY);
	sprintf_s(buf, "######## CCCPU started!");
	print_log(LOG_WARNING);
}

// 停机
void cccpu_stop() {
	sys_stop = clock();
	float sys_time = (float)(sys_stop - sys_start);
	float sys_frequency = 1000 * clock_cnt / sys_time;
	sprintf_s(buf, "######## WARNING");
	print_log(LOG_WARNING);
	sprintf_s(buf, "######## CCCPU stop at %I64d clock (%fms)!", clock_cnt, sys_time);
	print_log(LOG_WARNING);
	if (sys_frequency > 1000)
		sprintf_s(buf, "######## AVENUE sys_frequency is %f kHz", sys_frequency / 1000);
	else
		sprintf_s(buf, "######## AVENUE sys_frequency is %f Hz", sys_frequency);
	print_log(LOG_WARNING);
	exit(1);
}


int main() {
	signal(SIGINT, sig_handler);
	cccpu_restart();
	cccpu_controller();
	return 0;
}