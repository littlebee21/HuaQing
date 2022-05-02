# 一、常用伪操作

伪操作（Directive）：在程序运行中不起作用，因此也没有对应的机器编码。它们只在汇编和链接过程中起作用

按功能分为：

1. 符号定义伪操作

   全局标号声明伪操作.global：.global symbol    告诉汇编器该标号可以跨源文件使用

   局部标号定义伪操作 .local：.local symbol   告诉汇编器该标号不可以跨源文件使用，只能在本源文件使用

   宏替换伪操作:  类似于C语言#define，用来给常量起名字

   1.   .set symbol,expr   

    	2.   .equ symbol,expr   （推荐）

2. 数据定义伪操作:用于为特定的数据分配存储单元，同时可完成已分配存储单元的初始化

   .byte、.short、.word、.long、.string、.space、.skip

   [label:] .byte expr  ----------------  -2^7  ~ 2^8-1

   ​	例如：

   ​	DATA1: .byte  0xab   ------->  分配1个字节空间，并初始化为0x23，这1个字节空间的首地址用DATA1来表示，类似于C语言中语句：char DATA1 = 0xab

   ​	.byte 0x23  ------->分配1个字节空间，并初始化为0x23

      DATA2: .byte 0x12,0x34,0x56   ---------> 分配3个字节空间,并且分别初始化为0x12,0x34,0x56,这3字节空间的首地址用DATA2来表示

   

   [label:] .short expr  ---------------- -2^15  ~ 2^16-1 以2字节为单位分配空间

   

   [label:] .word expr  ---------------   -2^31 ~ 2^32-1   以4字节为单位分配空间

   [label:] .long expr  ----------------   同.word

   

   

   [label:] .string expr  -------------- 分配一块空间来存放字符串 

   例如：

   NAME: .string  "LaoWang"   -------->分配了strlen("LaoWang") + 1(指'\0') 个字节的空间，并用字符串常量“LaoWang”来给空间初始化，空间最后一个字符为字符串结尾符'\0',同时用NAME来表示该空间的首地址

   

   [label:] .space size,expr --------- 分配size个字节的空间，每个字节都用expr来初始化。同时可以用label来表示空间的首地址

   [label:] .skip size,expr --------- 同.space

   例如：

   ​	DATA: .space 10,0xFF  -------->分配10个字节的空间，每个字节都用0xFF来初始化。同时可以用DATA来表示空间的首地址

    

3. 汇编控制伪操作(了解)

   .if、.else、.endif

   .macro、.endm、.exitm

4. 杂项伪操作

   .data 用于定义一个数据段

   .text 用于定义一个代码段

   .include 用于包含一个头文件

   .end 代表源文件的结束

# 二、RISC-CPU的一大特点：Load/Store机制

RISC思想的CPU，用专门指令来访问内存，其它指令不能直接访问内存



Load类指令用于从内存中读数据到指定寄存器

Store类指令用于将指定寄存器中的内容保存到内存

# 三、访存指令之单寄存器的加载和存储

## 2.1 字数据和8位无符号字节数据Load和Store的寻址方式

基址变址寻址：在基础地址上做一些改变形成新地址

基址：基础地址，用寄存器来存放，因此这样的寄存器被称为基址寄存器

```
LDR|STR{cond}{B}{T} <Rd>,<address_mode>
<address_mode>有九种方式：访问内存用的地址是[]里计算出来的地址
不索引三种：先计算新地址但不更新基址寄存器，然后用新地址访问内存
[<Rn>,#+/-<offset_12>]

[<Rn>,+/-<Rm>]

[<Rn>,+/-<Rm>,<shift> #<shift_imm>]

前索引三种：先计算新地址并更新基址寄存器，然后用新地址访问内存

[<Rn>,#+/-<offset_12>]!

[<Rn>,+/-<Rm>]!

[<Rn>,+/-<Rm>,<shift> #<shift_imm>]!

后索引三种：先用基址寄存器的地址访问内存，然后计算新地址并更新基址寄存器

[<Rn>],#+/-<offset_12>

[<Rn>],+/-<Rm>

[<Rn>],+/-<Rm>,<shift> #<shift_imm>
```



## 2.2  半字数据和8位有符号字节数据Load和Store的寻址方式

```
LDR|STR{cond}H|SH|SB  <Rd>,<address_mode>
<address_mode>有如下六种方式:
不索引两种：
[<Rn>,#+/-<offset_8>]

[<Rn>,+/-<Rm>]

前索引两种：

[<Rn>,#+/-<offset_8>]!

[<Rn>,+/-<Rm>]!

后索引两种：
[<Rn>],#+/-<offset_8>

[<Rn>],+/-<Rm>
```



## 2.3 单寄存器Load/Store指令集

Load指令第一组： LDR、LDRB、LDRT、LDRBT

Store指令第一组：STR、STRB、STRT、STRBT

T标志表示在异常模式下使用该指令，使用用户模式的访存权限

第一组用的是第一套寻址方式（2.1节的9种）



Load指令第二组： LDRH、LDRSB、LDRSH

Store指令第二组：STRH

第二组用的是第二套寻址方式（2.2节的6种）

## 2.4 示例和练习

示例1：

```assembly
@判断字节序
.text		
.globl _start
_start:
	LDR R0,=0x11223344
	MOV R1,#0x40000000
	STR R0,[R1]
	LDRB R2,[R1]
	B .
.end
```

示例2：

```assembly
@将内存中的两个数相加并保存到内存
.text		
.globl _start
_start:
	LDR R0, =Value1 
	LDR R1, [R0] 
	LDR R0, =Value2 @ADD R0, R0, #0x4 
	LDR R2, [R0] 
	ADD R1, R1, R2 
	LDR R0, =Result 
	STR R1, [R0] 
	B .
.data
Value1: .word 0x11111111
Value2: .word 0x22222222
Result: .word 0x0
.end
```

练习1：

```assembly
@找内存中两个32位数的最大数，并将最大数保存到新的内存块
.text		
.globl _start
_start:
	LDR R0, =Value1 
	LDR R1, [R0],#4 
	LDR R2, [R0]
    
	CMP R1,R2
    MOVHI R3,R1
    MOVLS R3,R2
	
	LDR R0, =Result 
	STR R3, [R0] 
	B .
.data
Value1: .word 0x11111111
Value2: .word 0x22222222
Result: .word 0x0
.end
```



练习2:

```assembly
@将内存中的两个64位数相加，并将结果保存到新的内存块
```

```assembly
.text
.global _start
_start:
	LDR R6,=Value1
	LDR R0,[R6],#4
	LDR R1,[R6]
	
	LDR R6,=Value2
	LDR R2,[R6],#4
	LDR R3,[R6]
	
	ADDS R4,R0,R2
	ADC  R5,R1,R3
	
	LDR R6,=Result
	STR R4,[R6],#4
	STR R5,[R6]
	B .
	
.data
Value1: .word 0x12345678,0x12345678
.space 12,0x0
Value2: .word 0xF0000000,0x10000000
.space 8,0x0
Result: .word 0x0,0x0
```

示例3：

```assembly
@定义一个数组，数组中含4个32位数，求数组中元素的总和，并将结果保存到内存
.text		
.globl _start
_start:
	LDR R0,=Length
	LDR R2, [R0] 

	LDR R0, =Table 
	EOR R1, R1, R1 
Loop:
	LDR R3, [R0],#4
	ADD R1, R1, R3
	SUBS R2, R2, #0x1
	BNE Loop
	
	LDR R0, =Result
	STR R1, [R0]
	B .

.data
Table: .word 0x1000,0x2000,0x3000,0x4000
TablEnd: .word 0
Length: .word (TablEnd-Table)/4 
Result: .word 0 

.end

```



# 四、访存指令之批量加载存储

LDM|STM{<cond>}<address_mode>  <Rn>{!}, <register_list>{^}

编码格式：

![批量加载存储](.\批量加载存储.jpg)

Rn：为基址寄存器，用于存放内存块首地址

register_list：用{}括起来，用,分隔的多个寄存器，寄存器编号从小到大，连续编号可以写成Rn-Rm

U标志位：表示地址变化的方向，1时地址值向上变化（Upwards）

P标志位：表示基址寄存器所指的内存单元是否包含在指令使用的内存块内

W标志位：即指令中的!符号，表示指令执行后，基址寄存器<Rn>的值是否更新

L标志位表示操作的类型。1----store，0-----load

S标志位：即指令中的^符号，此标志不用于用户模式

	1. 寄存器列表中包含PC寄存器并且指令以LDM开头，S=1表示同时将SPSR的数值赋值到CPSR中
	2. 寄存器列表中不包含PC寄存器的LDM?和STM？指令，并且处理器模式为特权模式，S=1表示被操作的寄存器是用户模式下的物理寄存器，而不是当前特权模式的物理寄存器

address_mode：

​		由P标志和U标志两两组合，有以下4种通式批量加载存储：

1. IA（Increment After）：事后递增方式 LDMIA  STMIA

2. IB（Increment Before）：事先递增方式 LDMIB STMIB

3. DA（Decrement After）：事后递减方式 LDMDA STMDA

4. DB（Decrement Before）：事先递减方式  LDMDB STMDB

   由于顺序栈在程序中使用过于频繁，再衍生出4种栈式批量加载存储，这四种衍生出来是伪指令：

1. FD： Full Descending----满递减堆栈  
2. ED： Empty Descending----空递减堆栈 
3. FA： Full Ascending----满递增堆栈 
4. EA： Empty Ascending----空递增堆栈 

# 五、访存指令之通式批量加载存储

LDM|STM{<cond>}<address_mode>  <Rn>{!}, <register_list>{^}

批量从内存读数据到寄存器列表的指令：

1. LDMIA：事后递增方式
2. LDMIB：事先递增方式
3. LDMDA：事后递减方式
4. LDMDB：事先递减方式

批量将寄存器列表中的值保存到内存指令：

1. STMIA：事后递增方式
2. STMIB：事先递增方式
3. STMDA：事后递减方式
4. STMDB：事先递减方式

![四种批量存储模式](.\四种批量存储模式.jpg)

示例：块复制

```assembly
.equ num,20
.text
.global _start
_start:
	LDR R0,=src
	LDR R1,=dst
	MOV R2,#num

blockcopy: @以8个字为单位复制
	MOVS R3,R2,LSR #3   @除以2的3次方，得到以8个字为单位复制的次数
	BEQ copywords
octcopy:
	LDMIA R0!,{R4-R11}
	STMIA R1!,{R4-R11}
	SUBS R3,R3,#1
	BNE octcopy

copywords:@以单个字为单位复制
	ANDS R2,R2,#7 @总字数对8取余，得到剩余要复制的字数
	BEQ stop
wordcopy:
	LDR R3,[R0],#4
	STR R3,[R1],#4
	SUBS R2,R2,#1
	BNE wordcopy

stop:
	B stop
.data
src:
	.word 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4
dst:
	.word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

.end

```

# 六、访存指令之栈式批量加载存储

LDM|STM{<cond>}<address_mode>  <Rn>{!}, <register_list>{^}

Rn一般但不限于使用R13（SP）寄存器

批量出栈操作指令，即从内存读数据到寄存器列表的指令：

Full Decre

1. LDMFD：满递减  被替换为LDMIA  最常用
2. LDMFA：满递增  被替换为LDMDA
3. LDMED：空递减 被替换为LDMIB
4. LDMEA：空递增 被替换为LDMDB

批量入栈操作指令，即将寄存器列表中的值保存到内存指令：

1. STMFD：满递减 被替换为STMDB 最常用
2. STMFA：满递增 被替换为STMIB
3. STMED：空递减 被替换为STMDA
4. STMEA：空递增 被替换为STMIA



顺序栈分类1：按入栈时栈顶指针的地址值是增大还是减小分为    递增式栈   和   递减式栈

![增减顺序栈](.\增减顺序栈.jpg)



顺序栈分类2：按栈顶指向的内容是有效元素还是栈顶空位置分为    空堆栈   和  满堆栈

![空满顺序栈](.\空满顺序栈.jpg)

满递减栈在实际运用中主要完成子程序进入和退出时数据的保存和恢复，在调用子程序时：

1. 通常利用寄存器R0~R3传递参数和返回结果，这几个参数由子程序的调用者来保存
2. 子程序将要用到的寄存器在子程序入口处保存到内存（入栈）
3. 在子程序返回前恢复这些寄存器

使用模板：

```assembly
function:
	STMFD R13!,{R4-R12,R14} @入栈
	....
	Insert the function body here
	....
	LDMFD R13!,{R4-R12,PC} @出栈
```

从函数返回有3种方法
1. BX   LR
2. MOV PC,LR
3. LDM SP!,{....,PC} 注意前提是事先把LR的值存放在了栈中即STMFD SP!,{....,LR}    最通用



示例1：改写块复制

```assembly
.equ num,20
.text
.global _start
_start:
	LDR SP,=0x40002000 @设置栈区首地址

	LDR R0,=src
	LDR R1,=dst
	MOV R2,#num
	BL blockcopy

	B .

blockcopy: @以8个字为单位复制
	STMFD SP!,{R4-R11,LR}   @对调用处做现场保护
	
	MOVS R3,R2,LSR #3   @除以2的3次方，得到以8个字为单位复制的次数
	BEQ copywords
octcopy:
	LDMIA R0!,{R4-R11}
	STMIA R1!,{R4-R11}
	SUBS R3,R3,#1
	BNE octcopy

copywords:@以单个字为单位复制
	ANDS R2,R2,#7 @总字数对8取余，得到剩余要复制的字数
	BEQ stop
wordcopy:
	LDR R3,[R0],#4
	STR R3,[R1],#4
	SUBS R2,R2,#1
	BNE wordcopy
	
stop:
	LDMFD SP!,{R4-R11,PC} @现场恢复

	
.data
src:
	.word 1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4
dst:
	.word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

.end

```




# 七、访存指令之交换指令

又称信号量操作指令

信号量操作的实现需要用到原子操作，所谓原子操作就是不可被打断操作（要么没被执行，一执行就全部执行完，不会中途被打断）

SWP{<cond>}   <Rd>, <Rm>, [<Rn>]

SWPB{<cond>}   <Rd>, <Rm>, [<Rn>]

![swp](.\swp.jpg)

SWP R1,R2,[R3]    -------   将[R3]空间中值读入R1，然后将R2中的值保存到[R3]空间中

SWP R1,R1,[R2]   -------   将R1寄存器中的值与[R2]空间的值互换





作业1：

```assembly
@定义一个数组，数组中含4个32位无符号整数，找出最大值，并将结果保存到内存
```

作业2：

```assembly
/* 分配96个字节的空间并都初始化为0xAB，再分配96个字节空间并都初始化为0，将第一块空间复制到第二块空间
R12指向源数据起始地址
R14指向源数据尾地址
R13指向目的数据起始地址
每次复制48个字节
.space x,y 用于分配一块连续内存空间，占用x个字节，用y来进行初始化

loop:
	LDMIA R12!, {R0-R11}
	STMIA R13!, {R0-R11}
	CMP R12, R14
	BNE loop
*/
```



作业3：

```asm
@定义一个数组，数组中含6个32位无符号整数，试用冒泡法从大到小排序该数组，排序过程请封装成函数
```

