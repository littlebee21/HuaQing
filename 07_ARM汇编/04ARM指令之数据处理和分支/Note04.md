# 一、第一个汇编程序

```assembly
.text    
.globl _start
_start: 
	MOV R0,#3
	MOV R1,#4
	ADD R2,R0,R1
	B .
.end

/*
1. .开头位于行首的标识符，被称为伪操作，这些伪操作是为了辅助汇编器完成汇编
2. .text伪操作指示紧跟其后的内容为指令，应该放置到代码区
3. .end表示源文件的结尾，其后语句均不会被处理
4. 紧跟冒号的标识符，被称为标号，作为紧跟其后指令序列的功能名称，本质是紧跟其后指令序列在内存空间的首地址
5. _start标号为GNU汇编默认的汇编程序入口
6. .global表示其后的标号可以被跨源文件使用
7. 符号命名规范：0~9、大小写字母、“_”、“.”组成，区分大小写，不以数字开头
8. 指令、寄存器、伪操作关键字可以全大写，也可以全小写，但不建议大小混合
9. GNU建议伪操作顶行写，指令缩进写
*/
```

模拟调试运行

# 二、汇编程序中的语句

1. 指令：有对应机器码的指令，需要CPU执行的各种运算
2. 伪指令：形式类似于指令，但会被汇编器替换成同功能指令序列的语句
3. 伪操作：没有对应机器码的操作，它是用于告诉汇编程序如何进行汇编的操作语句，在汇编过程中起作用，运行中不起作用

# 三、三种注释

1. #开头的整行注释，只能注释一整行
2. @开头的行尾注释，即从@开始到行尾的内容被注释
3. /* */包裹的多行注释

# 四、ARM指令分类

1. 数据处理指令（重点）
   1. 数据传送指令：MOV MVN 
   2. 算术运算指令：ADD ADC SUB SBC RSB RSC
   3. 逻辑运算指令：AND ORR EOR BIC
   4. 比较指令：CMP CMN TST TEQ
2. 跳转指令：B（重点） BL（重点） BX（重点） BLX
3. 乘法运算指令：MUL MLA     SMULL SMLAL UMULL UMLAL
4. PSR传输指令（重点）：MRS  MSR
5. 访存指令（重点）：LDR STR LDM STM SWP
6. 异常产生指令：SWI（重点）  BKPT
7. 协处理器指令：CDP LDC STC MCR MRC

一般情况下，相同类的指令，具有同样寻址方式

寻址方式：操作数的来源方式

# 五、数据处理指令

```assembly
<opcode>{<cond>}{S}    <Rd>,<Rn>,<shifter_operand> @shifter_operand占低12位
```

shifter_operand的寻址方式：

1. 立即数：即第二操作数是一个受限的常数数值（立即数）

   立即数：由一个8位的常数循环右移偶数位所得，循环右移的位数由一个4位二进制数的两倍表示

   #开头的数值    #6（十进制）、#0xAB（十六进制），#056（八进制）#0b11（二进制）

   合法立即数的判断：1)将代码中写的立即数进过循环右移偶数个0后，能得到一个0~255之间数，那么这个立即数就是合法

   ​                                   2)将代码中写的立即数写成二进制，然后去掉高位所有的0，再去掉偶数个低位的0，如果能得到一个0~255的数即为合法立即数

2. 寄存器：即第二操作数是指定寄存器里存放的数据

   32位二进制编码的低4位指定寄存器编号

3. 寄存器移位：即第二操作数是指定寄存器里存放的数据经过移位处理后的结果

   移位的位数可以是1~32的数字或由某寄存器值的低8位指定：

   a.数字指定移位数：5位指定移位数，3位移位方式，4位指定寄存器编号

   b.寄存器指定移位数：4位指定寄存器编号，1位固定0，3位移位方式，4位指定寄存器编号

ARM移位机制：ARM指令集没有专门的移位指令，移位操作附件在数据处理指令中

![桶形移位器](.\桶形移位器.jpg)

移位方式：

1. ASR 算术右移：低位移出，高位补符号位（原数最高位）
2. LSL逻辑左移：高位移出，低位补0
3. LSR逻辑右移：低位移出，高位补0
4. ROR循环右移：移出的低位补到高位
5. RRX扩展的循环右移：一位，不可指定移位数，带上C位做一次循环右移

第二操作数寻址方式小结：

1. #<immediate>
2. <Rm>
3. <Rm>,LSL  #<shift_imm>
4. <Rm>,LSL  <Rs>
5. <Rm>,LSR  #<shift_imm>
6. <Rm>,LSR  <Rs>
7. <Rm>,ASR  #<shift_imm>
8. <Rm>,ASR  <Rs>
9. <Rm>,ROR  #<shift_imm>
10. <Rm>,ROR  <Rs>
11. <Rm>,RRX

## 5.1 数据传送指令

### MOV指令：`MOV{cond}{S}   <Rd>, <shifter_operand>`

功能：将shifter_operand表示的数据传送到目标寄存器<Rd>中

程序中的作用：

1. 将数据从一个寄存器传送到另一个寄存器中
2. 将一个立即数传送到一个寄存器中
3. 实现单纯的移位操作。左移可以实现操作数乘以2^n
4. 当R15(PC)作为目标寄存器时，可以实现程序跳转
5. 当R15(PC)作为目标寄存器且有S标志，除了跳转外，还会将对应的SPSR还原到CPSR



### MVN指令：`MVN{cond}{S}   <Rd>, <shifter_operand>`

功能：将shifter_operand表示的数据的反码传送到目标寄存器<Rd>中

## 5.2 算术运算指令

### ADD指令：`ADD{cond}{S}   <Rd>, <Rn>, <shifter_operand>`      

 Rd = Rn + shifter_operand

### ADC指令：`ADC{cond}{S}   <Rd>, <Rn>, <shifter_operand>`       

带进位的加法   Rd = Rn + shifter_operand+C

示例：64位的加法

```assembly
.text	   @abcd
.globl _start
_start:
	MOV R0,#0xff000000		@Low 32bits
	MOV R1,#0x10000000		@High 32 bits

	MOV R2,#0xff000000      @Low 32bits
	MOV R3,#0x20000000      @High 32bits

	ADDS R4,R0,R2
	ADC R5,R1,R3
	B .
.end
```



### SUB指令：`SUB{cond}{S}   <Rd>, <Rn>, <shifter_operand>`       

Rd = Rn - shifter_operand

### SBC指令：`SBC{cond}{S}   <Rd>, <Rn>, <shifter_operand>`        

带借位的减法  Rd = Rn - shifter_operand - （~C）



作业：实现64位的减法 

提交方式：sub64_姓名.S

上交日期：明日10:00前

```assembly
SUBS R4,R0,R2
SBC R5,R1,R3
```



### RSB指令：`RSB{cond}{S}   <Rd>, <Rn>, <shifter_operand>`        

逆向减 Rd = shifter_operand - Rn 

简化立即数做为被减数的情况

```assembly
@5-r2
mov R1,#5
sub R0,R1,R2

rsb R0,R2,#5
```



### RSC指令：`RSC{cond}{S}   <Rd>, <Rn>, <shifter_operand>`         

带借位的逆向减法 Rd = shifter_operand - Rn - （~C）



```assembly
@常用技巧
/*Rd = Rx *(2^n+1)*/
ADD R0,R1,R1,LSL #n

/*Rd = Rx *(2^n-1)*/
RSB R0,R1,R1,LSL #n

/*求64位的相反数，R0、R1放置一个64位数，R2,R3放置其相反数，R0、R2放置64位数低32位*/
RSBS R2,R0,#0
RSC R3,R1,#0

/*利用左移n位相当于乘以2的n次方，可以优化乘法*/
/*将R2中的值乘以4*/
MOV R2,R2,LSL #2

/*将R2中的值乘以5*/
ADD R2,R2,R2,LSL #2
```



## 5.3 逻辑运算指令：按位的位运算(两个操作数的所有位按位做运算)

### AND指令：`AND{cond}{S}   <Rd>, <Rn>, <shifter_operand>`       

Rd = Rn & shifter_operand

1. 程序中主要来将指定位 置0 (不太方便)

构造一个辅助数（掩码）来完成将指定位置0

AND R1,R1,#0xFFFFF7F3   不正确

 2. 判断指定位是1还是0

    判断R0的第6位是0还是1

    AND R1,R0,#0x40

### ORR指令：`ORR{cond}{S}   <Rd>, <Rn>, <shifter_operand>`       

Rd = Rn | shifter_operand

1. 程序中主要来将指定位 置1

将R0的第5位 置1，其它位不变：ORR R0,R0,#0x20

   2. 和BIC指令配合来给某寄存器的指定位范围赋值  

      ```assembly
      @将R0的低4位赋值为0b0101，其它位不变
      MOV R0,#0xAB
      BIC R0,R0,#0xF
      ORR R0,R0,#0b0101
      ```
      

### EOR指令：`EOR{cond}{S}   <Rd>, <Rn>, <shifter_operand>`      

 Rd = Rn ^ shifter_operand    相同为零，不同为1

程序中主要来将指定位 取反：构造掩码，掩码中所谓为1的位，与第一个操作数对应做异或，会将这些位取反

### BIC指令：`BIC{cond}{S}   <Rd>, <Rn>, <shifter_operand>`       

位清除：将指定位置0 

Rd = Rn & (~shifter_operand) 

BIC R1,R1,#0x800

BIC R1,R1,#0xC

```assembly
@常用技巧
/*判断R0的第2位为0还是1*/
AND R1,R0,#4

/*将r3寄存器中的第3、5位置0*/
BIC R3,R3,#0x28
AND R3,R3,#FFFFFFD7   @非法立即数

/*将r3寄存器中的第3、5位置1*/
ORR R3,R3,#0x28

/*将r3寄存器中的第3、5位取反*/
EOR R3,R3,#0x28

/*将r3寄存器中的低四位设置成0101，其它位不变*/
BIC R3，R3，#0xF
ORR R3，R3，#0b0101

/*将R2的高八位放置到R3的低八位，R3的其它位不变*/
MOV R0,R2,LSR #24
BIC R3,R3,#0xFF
ORR R3,R3,R0
```

```assembly
@测验
@1. 写一条 ARM 指令，分别完成下列操作：
@a) r0 = 16    
	MOV R0,#16
@b) r0 = r1 / 16 (带符号的数字)
	MOV R0,R1,ASR #4
@c) r1 = r2 * 3    
	ADD R1,R2,R2,LSL #1
@d) r0 = -r0   
	RSB R0,R0,0
	
@2. 下面哪些立即数是数据处理指令中有效的数据?
@a) 0x00AB0000 合法
@b) 0x0000FFFF 非法 
@c) 0xF000000F 合法
@d) 0x08000012 非法
@e) 0x00001f80 合法
@f) 0xFFFFFFFF 非法

@3. BIC指令做什么用？

@4. 为什么ARM 处理器增加了一条RSB 指令?
```



## 5.4 比较指令

没有S标志，这些指令只是为了设置CPSR高4位

这些指令不要计算结果，只要计算后CPSR高4位的状态

比较指令一般不会单独使用，往往是配合一些指令的条件助记符来实现选择执行

### CMP指令：`CMP{cond}   <Rn>, <shifter_operand>`       

Rn - shifter_operand  

SUBS

### CMN指令：`CMN{cond}   <Rn>, <shifter_operand>`       

Rn + shifter_operand

ADDS

### TST指令：`TST{cond}   <Rn>, <shifter_operand>`       

位测试 Rn & shifter_operand

ANDS

### TEQ指令：`TEQ{cond}   <Rn>, <shifter_operand>`       

相等测试 Rn ^ shifter_operand

EORS

# 六、跳转指令

这些指令只能实现短跳转，要实现任意范围的跳转用`MOV PC,<shifter_operand>`

### B指令：`B{cond}  <target_address>`

跳转到指定位置，target_address在二进制编码中占24位，一般用于局部范围内跳转，跳转范围-32M~32M

一般用来局部代码的循环实现

### BL指令：`BL{cond}  <target_address>`

带链接的跳转：保存PC到LR，跳转到指定位置，一般用于子程序调用

### BX指令：`BX{cond}   <Rm>`

带状态转换的跳转：跳转到指定位置，Rm的bits[0]为1切换为Thumb状态、bits[0]为0切换为ARM状态，一般用于子程序返回

### BLX指令1：`BLX  <target_address>`

保存PC到LR，跳转到指定位置，并切换为Thumb状态

### BLX指令2：`BLX{cond}    <Rm>`

保存PC到LR，跳转到指定位置，Rm的bits[0]为1切换为Thumb状态、bits[0]为0切换为ARM状态

# 七、LDR伪指令装载任意数

`LDR R0,=const` ：可以装载任意的32位常数

1. 这种形式LDR是伪指令
2. 汇编器遇到该行，发现如果mov可以的话，就改为使用mov指令来完成，如果mov不行的话，就借用内存来实现该数的装载
3. MOV与LDR伪指令的比较
   用mov来实现，占用空间小，速度快,但是对立即数有限制
   如果数比较大，用ldr r0,=const会多占空间，降低效率

在实际编程中，如果只是将一个常数赋值给一个寄存器，建议写成：LDR Rn,=常数

聪明的汇编器：

LDR R0,=0x1F  ---->  MOV R0,#0x1F

LDR R1,=0xABCD1234   ----> 将0xABCD1234放到内存，然后读内存数据到寄存器

MOV R2,#0xFFFFFFFF

# 八、课堂示例与练习1：选择语句的实现

```assembly
/*
if(a > b)
{
	a++;
}
else
{
	b++;
}
*/
.text
.globl _start
_start:
	MOV R0,#2
	MOV R1,#1
	CMP R0,R1
	ADDHI R0,R0,#1
	ADDLS R1,R1,#1
	
	b .
.end
```

练习1：判断奇偶数

```assembly
/*已知r0中有一个数值，如果其为奇数则将r1中置1否则置0*/
.text
.globl _start
_start:
	MOV R0,#2
	TST R0,#1
	MOVEQ R1,#0
	MOVNE R1,#1

	B .
.end
```

# 九、课堂示例与练习2：循环语句的实现

示例1：

```assembly
/*求1到100的和*/
.text
.globl _start
_start:
	MOV R0,#100
	MOV R2,#0
loop:
	ADD R2,R2,R0
	SUBS R0,R0,#1
	BNE loop
	
	B .
.end
```

练习1:辗转相减法求两个数的最大公约数

```c
#include<stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	printf("please Enter 2 datas:");
	scanf("%d %d",&a,&b);
	while(1)
	{
		if(a>b)
		{
			a = a-b;//将两个数的差值赋给最大的一个
		}
		else if(a<b)
		{
			b = b-a;
		}
		else 
		{
			printf("%d\n",b);
			break;//跳出整个循环
		}
	}
	return 0;
}
```





# 十、汇编模拟函数调用

## 9.1 如何在汇编中实现函数调用

`BL func`进行函数调用

## 9.2 函数中如何返回

两种方法：

1. `BX LR`     更通用一些，可以在Thumb和ARM间互相调用
2. `MOV PC,LR` 

PC R15 里面存放将要执行的指令的地址
LR R14 里面存放要返回到的指令的地址

一般在实际编程中：R13写成SP，R14写成LR，R15写成PC

## 9.3 函数调用过程中如何传参：

参数依次用r0,r1,r2,r3来进行传递
函数的返回值首选r0来进行传递，如果有两个结果则首先R0，R1，。。。。。。



## 9.4 函数定义和调用的模板

```assembly
/*函数调用*/
@......
@.....
@.....

@通过给R0、R1、R2、R3设置值，来向func函数传递参数，用几个寄存器，根据函数的参数个数决定,绝大多数函数的参数个数不会超过4个
BL func  @调用函数

@.....

/*函数定义*/
func:
	@...功能实现
	@通过给R0设置值，来向函数调用处返回实现结果，如果结果有多个则继续使用R1、R2....,绝大多数函数的实现结果是一个
	BX LR @函数返回

```



# 十一、课堂示例与练习3：函数调用的实现

示例1：

```assembly
.text
.globl _start
_start:
	MOV R0,#3
	MOV R1,#5
	BL foo
	B .
foo:
	ADD R0,R0,R1
	MOV PC,LR @BX LR
		
.end
```

练习1：改写辗转相减求最大公约数，即将求最大公约数封装成函数

```assembly
@参考代码
.text
.global _start
_start:
	MOV R0,#9
	MOV R1,#15
loop:
	CMP R0,R1
	BEQ stop
	SUBGT R0,R0,R1
	SUBLT R1,R1,R0
	B loop
	
stop:
	B stop
.end

@函数式的求最大公约数
.text
.global _start
_start:
	MOV R0,#6
	MOV R1,#12
	BL gcd
	B .
	
gcd:
	CMP R0,R1
	BXEQ LR
	SUBGT R0,R0,R1
	SUBLT R1,R1,R0
	B gcd
	
.end
```

实际编程中尽量少用整数乘法，因为乘法效率很差，尽量采用左移来实现

ARM指令集中没有整数除法指令，遇到除法，则采用右移来实现，或者用减法来实现

示例2：

```assembly
@实现简单的正整数除法
.text
.globl _start
_start:
	mov r0,#16
	mov r1,#3
	bl div


stop:
	b stop
div:
	mov r2,#0
loop:
	cmp r0,r1
	bcc xxx
	subs r0,r0,r1
	add r2,r2,#1
	b loop
xxx:
	mov r1,r0
	mov r0,r2
	bx lr
	 	
.end

```



# 十二、作业

作业1：将C语言代码写成汇编代码

```c
/*猴子吃桃问题
有一只猴子摘了一堆桃子,当即吃了一半,又再多吃了一个.
以后每天重复,到第10天发现只有1个桃子了
问最开始摘了多少个桃子*/
#include <stdio.h>

int main()
{
    int x=1;
    int day=10;
    while(--day)
    {
        x=(x+1)*2;
        printf("day=%d,x=%d\n",day,x);
    }
    return 0;
}
```

源码文件命名要求：monkey.s

```assembly
@monkey.s
.text
.global _start
_start:
	MOV R1,#9
	MOV R0,#1
	
loop:
	ADD R0,R0,#1
	MOV R0,R0,LSL #1
	SUBS R1,R1,#1
	BNE loop
	
	B .
.end
```



作业2：求长方形周长，长宽为整数，要求计算周长封装成函数

源码文件命名要求：rect_c.s

```assembly
@rect_c.s
.text
.global _start
_start:
	MOV R0,#3   @length
	MOV R1,#4   @width
	BL RECT_C
	B .
	
RECT_C:
	ADD R2,R0,R1
	MOV R0,R2,LSL #1
	BX LR
	
.end
```



作业提交要求：将monkey.s和rect_c.s做成压缩包文件，压缩包文件命名为：hw0417\_姓名.rar或hw0417\_姓名.zip







C语言函数调用步骤：

传参：

1. 执行函数形参定义语句（这些参数要么用内存，要么用CPU寄存器）
2. 计算实参表达式的值，并将计算结果赋值给对应形参
3. 跳转进函数体执行语句
4. 执行完函数体或执行return语句返回到调用处



函数调用：一次函数调用就是使用一次函数功能   --------- 使用工具

函数定义：实现函数功能  ------- 制造一个工具