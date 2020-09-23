# CCCPU

尝试用C++模拟一个符合冯诺依曼架构的计算机。

## 计划

**使用方案**
- 输入：memory.txt
- 输出：print.txt
- 内存调试：dump.txt
- 配置：config.ini

**计划格式**

*config.ini*
- 字长(?)
- 时钟最高频率
- 开始执行位置
- 输出文件and格式 `可以添加多个输出`
  - 文件名
  - 输出进制
- 输出内存做调试
  - 文件名
  - 输出进制
  - 格式和输入文件一样

*memory.txt*
- 按照规定的字长的两倍组成一行，按照行来分割单个指令和数据
- 从第`0000`位开始执行
- 先是指令区然后是数据区，即第一个停机指令之后是数据区
- 使用`//`或者`;`之后作为注释，`/**/`之间也可以是注释
- 可以用`[数字]`指示储存位置
- 数字默认为2进制，`0xFF`表示16进制, `0d99`表示10进制，有效到下一个空白符号或者非法符号出现
- 空行忽略
- 每个储存单元高位存指令，低位存地址码，都是一个字长
- 数据可以有两个字长
- 行中存在空格则从左往右计算字长，字长不够在高位补零
- `↑写指令的时候注意把地址码填满字长`

*print.txt*
- 默认文件名
- 按照格式输出

**计算机架构**

*运算器*
- 寄存器
  - 加法寄存器
  - 乘法寄存器
  - 通用寄存器

*控制器*
- 时钟`CLK`
  - 休眠指定时间触发一次
  - 触发则执行任务序列的函数
- 程序计数器`PC`
  - 每一个CLK都会自增1
  - 溢出会强制停机
- 指令寄存器`IR`
  - 

*储存器*
- 结构
  - 内容寄存器`STC`
  - 地址寄存器`STR`
- 特点
  - 工作周期是一个节拍
  - 能在一个工作周期内取出指定地址中的内容
  - （理解为一直在运行，不断抽出储存单元的地址

**运行过程**

*机器周期`CLE`*
- 发送指令地址给存储器(1CLK)
- 取出存储器中的指令给控制器(1CLK)
- 控制器解析指令(1CLK)
- 控制相关动作执行(1CLK)

*时钟原理*
- 先计算出单次时钟间隔
- 睡眠到这个时间结束然后开始执行/使用while控制最小粒度
- 指示取出指令(CLK1)(`PC` -> `STR`)
- 指令取出完成(CLK2)(`STC` -> `IR`)
- `PC`自增，检查`PC`溢出，溢出则停机(CLK3)
- 读取任务列表(函数指针数组)，执行列表中的函数
  - 执行参数：【无】
- 注意是任务列表，依次执行，不使用多线程(以后可能会用)(CLK4)


**指令集**

*数据计算操作*
- 取数(2CLK)
- 存数(2CLK)
- 加法(1CLK)
- 乘法(1CLK)

*过程指令*
- 跳转(1CLK)
- 停机
- 重启

*操作指令*
- 打印(1CLK)
- 调试：输出储存器的值(1CLK)
- 调试：输出寄存器的值(1CLK)

## 工程结构

**class CCCPU**
- CCCPU:`Units`元件
  - *Units::`REG`寄存器(基类)*
  - *Units::`ALF`可执行运算(基类)*
- CCCPU::`ALU`运算器
  - (REG)`ADD`加法寄存器
  - (REG)`MLT`乘法寄存器
  - (REG)`COM`通用寄存器
  - (ALF)`XAD`加法
  - (ALF)`XMT`乘法
- CCCPU::`CTL`控制器
  - CTL::`CLK`节拍发生器
  - CTL::`SIG`信号控制器
  - (REG)`PC`程序计数器
  - (REG)`IR`指令寄存器
- CCCPU::`STO`储存器
  - (REG)`STR`地址寄存器
  - (REG)`STC`内容寄存器