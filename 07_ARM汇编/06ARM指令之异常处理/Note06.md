# 一、七种异常

执行流：从开始到结束总体上顺序执行的一段代码：

	1. 正常执行流
 	2. 异常执行流：当异常发生时，打断正常执行的程序，跳转到指定位置执行异常处理程序，在异常处理程序执行完后再返回继续正常的程序执行



函数和异常处理程序的比较：

1. 函数调用是正常程序的跳转执行，它与顺序执行的代码同属一个执行流，处于同一运行模式。异常处理程序是处理异常情况的代码，它与被打断的正常程序不属同一执行流，运行在不同模式
2. 函数调用是正常程序的逻辑需求，跳转的发生按功能逻辑的要求发生。异常产生的时间大多具有不确定性，被打断的正常程序位置也大多不确定，与正常程序的逻辑没有直接关联
3. 函数调用和异常处理程序都需要做现场保存和恢复现场，但异常处理程序还需要做模式切换、备份恢复PSR、现场保存和恢复现场所用寄存器也有所不同
4. 函数调用与它所属执行流使用同一个栈，而异常处理程序用自己的专用栈
5. 函数代码所处内存位置在链接时确定，异常处理程序的入口由CPU指定固定内存位置

![异常含义](.\异常含义.jpg)

| 异常向量地址 | 异常名称     | 运行模式 | 模式位  | 优先级（6最低） | 可使用的寄存器                              |
| ------------ | ------------ | -------- | ------- | --------------- | ------------------------------------------- |
| 0x0          | 复位         | SVC      | 0b10011 | 1               | PC，CPSR，R12-R0，R14_svc-R13_svc，SPSR_svc |
| 0x4          | 未定义指令   | UND      | 0b11011 | 6               | PC，CPSR，R12-R0，R14_und-R13_und，SPSR_und |
| 0x8          | 软中断       | SVC      | 0b10011 | 6               | PC，CPSR，R12-R0，R14_svc-R13_svc，SPSR_svc |
| 0xc          | 指令预取中止 | ABT      | 0b10111 | 5               | PC，CPSR，R12-R0，R14_abt-R13_abt，SPSR_abt |
| 0x10         | 数据访问中止 | ABT      | 0b10111 | 2               | PC，CPSR，R12-R0，R14_abt-R13_abt，SPSR_abt |
| 0x14         | 保留         | 未使用   | 未使用  | 未使用          | 未使用                                      |
| 0x18         | 普通中断请求 | IRQ      | 0b10010 | 4               | PC，CPSR，R12-R0，R14_irq-R13_irq，SPSR_irq |
| 0x1c         | 快速中断请求 | FIQ      | 0b10001 | 3               | PC，CPSR，R7-R0，R14_fiq-R8_fiq，SPSR_fiq   |

注：User模式位0b10000，System模式位0b11111，可使用的寄存器PC，CPSR，R14-R0

![异常向量表](.\异常向量表.jpg)

# 二、模式切换

现代化的高端CPU都会有多种工作模式
ARM有八种模式，分为两类： 

1. 权限受到限制的模式即：用户模式  
2. 特权模式，它再分为：
   1. 正常特权模式：系统模式、监控模式
   2. 异常特权模式：管理模式、中断模式、快中断模式、中止模式、未定义模式

ARM上电启动时，处于SVC模式

操作系统的正常代码平时运行也是运行在SVC模式

异常产生时，ARM处理器将自动切换成异常对应的运行模式去运行异常处理程序

异常处理程序结束后通过将对应的SPSR拷贝回CPSR还原到异常发生前的运行模式

其它情况需要进行手动模式切换，包括：

1. SVC模式切换成用户模式、系统模式或监控模式
2. 异常模式切换成系统模式

# 三、PSR访问指令

手动切换模式、中断屏蔽、中断恢复需要修改PSR寄存器，而修改PSR寄存器需要用专用指令：MRS/MSR

通常通过“读取-修改-写回”操作序列修改PSR的内容

## 3.1 MRS：将状态寄存器的内容传送到通用寄存器中

MRS{<cond>}    <Rd>, CPSR | SPSR



## 3.2 MSR：将通用寄存器的内容或一个立即数传送到PSR中

MSR{<cond>}   CPSR_<fields>, #<immediate>

MSR{<cond>}   CPSR_<fields>, <Rm>

MSR{<cond>}   SPSR_<fields>, #<immediate>

MSR{<cond>}   SPSR_<fields>, <Rm>

<fields>设置PSR中需要操作的位：（可以单个也可组合也可不写表示全部）

1. bits[7:0]为控制位域，用c表示 ，大多情况下我们手动操作该域
2. bits[15:8]为扩展位域，用x表示
3. bits[23:16]为状态位域，用s表示
4. bits[31:24]为条件标志位域，用f表示

## 3.3 “读取-修改-写回”方式修改PSR的典型代码：

```assembly
@切换工作模式
MRS R0,CPSR
BIC R0,R0,#0x1F
ORR R0,R0,#0x13
MSR CPSR,R0   @MSR CPSR_c,R0
```



# 四、异常处理

## 4.1 处理器对异常的响应

```pseudocode
/*以下操作是ARM处理器自动完成*/
LR_<exception_mode> = return link       /*将下一条指令的地址保存到LR（PC-4），方便异常处理程序返回后，继续执行被打断的代码*/
SPSR_<exception_mode> = CPSR            /*将CPSR备份到异常模式对应的SPSR，为了保护被打断的代码的现场，确保其按原本逻辑继续执行*/
CPSR[4:0] = exception_mode_number   /*设置模式位进行模式切换*/

/*进入ARM状态*/
CPSR[5] = 0  /*异常处理程序的入口和返回都必须是ARM指令*/

IF <exception> == reset or FIQ THEN
{
	/*屏蔽快速中断FIQ*/
	CPSR[6] = 1
}

/*屏蔽普通中断IRQ*/
CPSR[7] = 1	

PC = exception_vector_address  /*跳转到指定异常向量表的对应位置去执行异常处理程序*/
```

## 4.2 从异常处理程序中返回

**在ARM架构里，PC值指向当前执行指令地址加8**  （不管流水线级数是多少，都是按三级流水线的方式去理解）

**BL跳转和异常响应时，处理器会将PC-4保存到对应LR中**

**异常处理程序返回时，针对不同的异常，对恢复到PC的LR，可能需要做一些对应性调整**

![流水线示例图](.\流水线示例图.jpg)



1. SWI和未定义指令异常：由当前执行的指令自身产生的，两种异常产生时，PC值未更新

   此时PC = 当前指令地址+8，下一条指令地址=PC - 4 （LR）

2. IRQ和FIQ异常：处理器执行完当前指令后，查询IRQ及FIQ中断引脚并且查看是否允许响应中断，因此这两种异常产生时，PC值已更新

   此时PC = 当前指令地址+12，下一条指令地址=PC - 8 ，而LR保存的是PC - 4，因此返回时需要LR - 4

3. 指令预取中止异常：在指令预取时，如果目标地址是非法的，该指令将被标记成有问题的指令。此时，流水线上该指令之前的指令继续执行。当执行到该被标记成有问题的指令时，处理器产生指令预取中止异常。当发生指令预取中止异常时，程序要返回到产生该异常的指令处，而不是返回到其下一条指令，这是为了方便重新取指

   此时PC = 当前指令地址+8，下一条指令地址=PC - 4 （LR），因此返回时需要LR - 4

4. 数据访问中止异常：当发生数据访问中止异常时，程序要返回到该有问题的数据访问处，这是为了方便重新数据访问。该异常是由数据访问指令产生的，此时PC值已更新

   此时PC = 当前指令地址+12，而LR保存的是PC - 4，因此返回时需要LR - 8

5. 复位异常无需返回

![异常返回](.\异常返回.jpg)



各种异常返回时的指令：

1. SWI和未定义指令异常：

   简单返回：`MOVS   PC, LR`  此时S表示将SPSR_svc或SPSR_und拷贝到CPSR，前提:a. 目标寄存器是PC b. 工作在异常模式

   操作了栈时返回：

   ```assembly
   LDR  SP_mode, = StackAddress
   
   STMFD   SP!, {reglist,LR}
   /*.......*/
   LDMFD  SP!, {reglist,PC}^  @此时^表示将SPSR_svc或SPSR_und拷贝到CPSR
   ```

   ​		 

2. IRQ和FIQ异常、指令预取中止异常：操作了栈时返回:

   简单返回：`SUBS  PC, LR, #4` 此时S表示将SPSR_irq或SPSR_fiq或SPSR_abt拷贝到CPSR，前提:a. 目标寄存器是PC b. 工作在异常模式

   操作了栈时返回:

   ```assembly
   LDR  SP_mode, = StackAddress
   SUBS  LR, LR, #4
   STMFD   SP!, {reglist,LR}
   /*.......*/
   LDMFD  SP!, {reglist,PC}^  @此时^表示将SPSR_irq或SPSR_fiq或SPSR_abt拷贝到CPSR
   ```

   FIQ比IRQ快的三个原因：

   1. 优先级FIQ高于IRQ
   2. FIQ具有私有的R8-R12
   3. FIQ位于异常向量表最末

3. 数据访问中止异常

   简单返回：`SUBS  PC, LR, #8` 此时S表示将SPSR_abt拷贝到CPSR，前提:a. 目标寄存器是PC b. 工作在异常模式

   操作了栈时返回:

   ```assembly
   LDR  SP_mode, = StackAddress
   SUBS  LR, LR, #8
   STMFD   SP!, {reglist,LR}
   /*.......*/
   LDMFD  SP!, {reglist,PC}^  @此时^表示将SPSR_abt拷贝到CPSR
   ```



## 4.3 异常向量表的设置

子程序和函数的使用 ------ 调用

异常发生时对异常处理程序---------不称调用，而称跳转到固定位置

简易版：

```assembly
Vector_Init_Block：
B Reset_Handler
B Undefined_Handler
B SWI_Handler
B Prefetch_Handler
B Abort_Handler
NOP
B IRQ_Handler
B FIQ_Handler

Reset_Handler: @启动代码
	......
	
SWI_Handler: @软中断异常处理程序
	.....
	
Undefined_Handler:@未定义指令异常处理程序
	.....

Prefetch_Handler:@指令预取异常处理程序
	.....
	
Abort_Handler:@数据访问异常处理程序
	.....
	
IRQ_Handler:@普通中断异常处理程序
	.....
	
FIQ_Handler:@快中断异常处理程序
	.....

```

通用版：

```assembly
Vector_Init_Block：
LDR PC, Reset_Addr
LDR PC, Undefined_Addr
LDR PC, SWI_Addr
LDR PC, Prefetch_Addr
LDR PC, Abort_Addr
NOP
LDR PC, IRQ_Addr
LDR PC, FIQ_Addr
Reset_Addr:.word Start_Boot
Undefined_Addr: .word Undefined_Handler
SWI_Addr: .word SWI_Handler
Prefetch_Addr: .word Prefetch_Handler
Abort_Addr: .word Abort_Handler
.word 0
IRQ_Addr: .word IRQ_Handler
FIQ_Addr: .word FIQ_Handler

Start_Boot:
	......
	
SWI_Handler:
	.....
	
Undefined_Handler:
	.....

Prefetch_Handler:
	.....
	
Abort_Handler:
	.....
	
IRQ_Handler:
	.....
	
FIQ_Handler:
	.....

```



# 五、软中断的产生和处理

SWI{<cond>}   <immed_24>

immed_24：一个24位的正整数，用来区分不同的SWI功能

SWI异常主要用于用户模式的应用程序可以调用SVC模式下的代码，在操作系统中，通常使用SWI异常为app提供**系统功能调用**（简称**系统调用**）

![swi异常处理程序框架](.\swi异常处理程序框架.jpg)

SWI异常处理的模板同样可以适用于其它异常处理，模板大体上是雷同的，某些位置的指令需要做些微调

## 5.1 第1级SWI异常处理程序

```assembly
SWI_Handler:
	LDR SP,=SP_ADDR @设置栈指针
	STMFD SP!,{R0-R12,LR}  @保存用到的寄存器
	
	LDR R0,[LR,#-4] @获取该SWI指令的地址
	BIC R0,R0,#FF000000 @得到SWI指令中的24位正整数
	/*
	使用R0寄存器中的值，调用相应的SWI异常第2级处理程序
	*/
	LDMFD SP!,{R0-R12,PC}^
	
```

## 5.2 第2级SWI异常处理程序之汇编版

```assembly
CMP R0,#MaxSWI   @MaxSWI表示支持功能数,可以用.equ MaxSWI,4来指定值，判断本次调用的功能号是不是在允许范围，R0取值范围是[0~MaxSWI-1]
LDRLS PC,[PC,R0,LSL #2] @跳转到相应位置,[PC+R0*4}
B SWIOutOfRange @错误处理
SWIJumpTable:
	.word SWINum0
	.word SWINum1
	/*
	..........other .word SWINum?
	*/
	
SWINum0:
	/*0号功能实现*/
	B EndOfSWI
SWINum1:
	/*1号功能实现*/
	B EndOfSWI
/*
SWINum?:
	@?号功能实现
	B EndOfSWI
*/
SWIOutOfRange:
	@.....
EndOfSWI:
	@.....
```

## 5.3 第2级SWI异常处理程序之C语言版

### 5.3.1 所有功能无需传参版本

第2级异常处理程序C语言模板

```c
//number 为第1级SWI处理程序中通过R0传过来的24位功能号
void C_SWI_Handler(unsigned number)
{
    switch(number)
    {
        case 0:
            /*0号功能实现*/
            break;
        case 1:
            /*1号功能实现*/
            break;
        /*
        case ?:
        	//?号功能实现
        	break;
        */
        default:
            break;
    }
}
```

此时第1级调用第2级的代码为：

```assembly
BL C_SWI_Handler
```

### 5.3.2 各功能需要额外传参版本

此处功能参数不同于第2级处理函数的参数

```c
//number 为第1级SWI处理程序中通过R0传过来的24位功能号
//pStack 为第1级SWI处理程序中通过R1传过来的栈指针
void C_SWI_Handler(unsigned number,unsigned *pStack)
{
    //功能额外参数的读取
    value_in_reg_0 = pStack[0];
    value_in_reg_1 = pStack[1];
    value_in_reg_2 = pStack[2];
    value_in_reg_3 = pStack[3];
    
    /*各功能号实现*/
    /*..........*/
    
    /*各功能的返回结果*/
    pStack[0] = updated_value0;
    pStack[1] = updated_value1;
    pStack[2] = updated_value2;
    pStack[3] = updated_value3;
}
```

此时第1级调用第2级的代码为：

```assembly
MOV R1,SP
BL C_SWI_Handler
```

## 5.4 示例

#### 无参单功能版：

```assembly
.text
.global _start
_start:
Vector_Init_Block:
	B Reset_Handler
	B .
	B SWI_Handler
	B .
	B .
	NOP
	B .
	B .

Reset_Handler:
	LDR SP,=0x40002000
	@切换为用户模式
	MRS R0,CPSR
	BIC R0,R0,#0x1F
	ORR R0,R0,#0x10
	MSR CPSR,R0
	
	SWI 0x11 @调用0x11号功能
	B .

SWI_Handler:
	STMFD SP!,{R0-R12,LR}  @保存用到的寄存器
	LDR R0,[LR,#-4] @获取该SWI指令的地址
	BIC R0,R0,#0xFF000000 @得到SWI指令中的24位正整数
	
	CMP R0,#0x11
	BNE SWI_END
	LDR R1,=V1
    LDR R2,[R1],#4
    LDR R3,[R1],#4
    ADD R0,R2,R3
	
SWI_END:
	STR R0,[R1]
	LDMFD SP!,{R0-R12,PC}^


.data
V1: .word 0x1
V2: .word 0x2
Ret: .word 0
.end

```

#### 无参多功能版

```assembly
.equ MaxSWI,4
.text
.global _start
_start:
Vector_Init_Block:
	B Reset_Handler
	B .
	B SWI_Handler
	B .
	B .
	NOP
	B .
	B .

Reset_Handler:
	LDR SP,=0x40002000
	@切换为用户模式
	MRS R0,CPSR
	BIC R0,R0,#0x1F
	ORR R0,R0,#0x10
	MSR CPSR,R0
	
	SWI 0x11 @调用0x11号功能
	B .

SWI_Handler:
	STMFD SP!,{R0-R12,LR}  @保存用到的寄存器
	LDR R0,[LR,#-4] @获取该SWI指令的地址
	BIC R0,R0,#0xFF000000 @得到SWI指令中的24位正整数
	
	BL SWI_Handler2
	
SWI_END:
	LDMFD SP!,{R0-R12,PC}^

/*第2级处理程序开始*/
SWI_Handler2:
	CMP R0,#MaxSWI
	LDRCC PC,[PC,R0,LSL #2] @跳转到相应位置
	B SWIOutOfRange @错误处理
SWIJumpTable:
	.word SWINum0
	.word SWINum1
	.word SWINum2
	.Word SWINum3
	
SWINum0:/*0号功能实现 --- 加*/
	CMP R0,#0x0
	BNE SWIOutOfRange
	LDR R1,=V1
    LDR R2,[R1],#4
    LDR R3,[R1],#4
    ADD R0,R2,R3
	B EndOfSWI2
SWINum1:/*1号功能实现 --- 减*/
	CMP R0,#0x1
	BNE SWIOutOfRange
	LDR R1,=V1
    LDR R2,[R1],#4
    LDR R3,[R1],#4
    SUB R0,R2,R3
	B EndOfSWI2
SWINum2:/*2号功能实现 --- 与*/
	CMP R0,#0x2
	BNE SWIOutOfRange
	LDR R1,=V1
    LDR R2,[R1],#4
    LDR R3,[R1],#4
    AND R0,R2,R3
	B EndOfSWI2
SWINum3:/*3号功能实现 --- 或*/
	CMP R0,#0x3
	BNE SWIOutOfRange
	LDR R1,=V1
    LDR R2,[R1],#4
    LDR R3,[R1],#4
    ORR R0,R2,R3
	B EndOfSWI2

EndOfSWI2:
	STR R0,[R1]
SWIOutOfRange:
	BX LR
/*第2级处理程序结束*/


.data
V1: .word 0x3
V2: .word 0x2
Ret: .word 0
.end


/*第二级C函数*/
void SWi2_Handler(int no)
{
	switch(no)
	{
		case 0:
			....
			break;
		case 1:
			....
			break;
		...
	}
}

```



#### 带参功能版

```assembly
.text
.global _start
_start:
Vector_Init_Block:
	B Reset_Handler
	B .
	B SWI_Handler
	B .
	B .
	NOP
	B .
	B .

Reset_Handler:
	LDR SP,=0x40002000
	@切换为用户模式
	MRS R0,CPSR
	BIC R0,R0,#0x1F
	ORR R0,R0,#0x10
	MSR CPSR,R0
	
	MOV R0,#1
	MOV R1,#2
	SWI 0x11 @调用0x11号功能
	B .

/*SWI第1级处理程序开始*/
SWI_Handler:
	STMFD SP!,{R0-R12,LR}  @保存用到的寄存器
	LDR R0,[LR,#-4] @获取该SWI指令的地址
	BIC R0,R0,#0xFF000000 @得到SWI指令中的24位正整数
	
	MOV R1,SP
    BL C_SWI_Handler
	
SWI_END:
	
	LDMFD SP!,{R0-R12,PC}^
/*SWI第1级处理程序结束*/


.data
V1: .word 0x1
V2: .word 0x2
Ret: .word 0
.end

void C_SWI_Handler(unsigned number,unsigned *pStack)
{
	int x = pStack[0];
	int y = pStack[1]
	
	int z = x + y;
	pStack[0] = z;
}
```



作业：利用swi指令实现一个系统功能，该功能要求3个整数返回其中最大数，要求第二级swi处理用C语言实现

提交日期：8月11日9:00前

提交要求：源码命名为：findmaxcall_姓名.zip/rar

```assembly
/*参考代码--汇编版*/
.text
.global _start
_start:
Vector_Init_Block:
	B Reset_Handler
	B .
	B SWI_Handler
	B .
	B .
	NOP
	B .
	B .

Reset_Handler:
	LDR SP,=0x40002000
	@切换为用户模式
	MRS R0,CPSR
	BIC R0,R0,#0x1F
	ORR R0,R0,#0x10
	MSR CPSR,R0
	
	MOV R0,#11
	MOV R1,#222
	MOV R2,#33
	SWI 0x11 @调用0x11号功能
	B . @结果在R0中

/*SWI第1级处理程序开始*/
SWI_Handler:
	STMFD SP!,{R0-R12,LR}  @保存用到的寄存器
	LDR R0,[LR,#-4] @获取该SWI指令的地址
	BIC R0,R0,#0xFF000000 @得到SWI指令中的24位正整数
	
	CMP R0,#0x11
	BNE SWI_END

	/*1. 从栈区读取系统功能所需参数*/
	LDR R1,[SP]
	LDR R2,[SP,#4]
    LDR R3,[SP,#8]
    
    /*2. 系统功能实现*/
    CMP R1,R2
    MOVLS R1,R2
    CMP R1,R3
    MOVLS R1,R3
    
    /*3. 将系统功能产生的结果存放到栈顶位置（即swi指令前的R0入栈位置）*/
    STR R1,[SP]    
	
SWI_END:
	LDMFD SP!,{R0-R12,PC}^
/*SWI第1级处理程序结束*/


.end


```

