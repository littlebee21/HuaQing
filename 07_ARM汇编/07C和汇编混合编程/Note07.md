# 一、两种混编方式

1. 过程调用
   1. 汇编调用C函数
   2. C语言调用汇编子程序
2. C语言内嵌汇编（内联汇编）

# 二、过程调用标准ATPCS

ARM/Thumb Procedure Call Standard ------  ARM/Thumb过程调用标准，规定了一些子程序间调用的基本规则、寄存器的使用规则、堆栈的使用规则和参数的传递规则等

## 2.1 寄存器的使用规则


　　寄存器r0~r3：子程序之间通过r0~r3来传递参数，当参数个数多于4个时，使用堆栈来传递参数。此时r0~r3可记作A1~A4。

　　寄存器r4~r11：在子程序中使用r4~r11保存局部变量。因此当进行子程序调用时要注意对这些寄存器的保存和恢复。此时r4~r11可记作V1~V8。

　　寄存器r12：用于保存堆栈指针SP，当子程序返回时使用该寄存器出栈，记作IP。

　　寄存器r13：堆栈指针，记作SP。

　　寄存器r14：链接寄存器，记作LR。用于保存子程序的返回地址。

　　寄存器r15：程序计数器，记作PC。

## 2.2 堆栈的使用规则


　　ATPCS规定堆栈采用满递减类型(FD, Full Descending)，即堆栈通过减小存储器地址而向下增长，堆栈指针指向内含有效数据项的最低地址。

## 2.3 参数的传递规则


　　整数参数：前4个使用r0~r3传递，其他参数使用堆栈传递；浮点参数：使用编号最小且能够满足需要的一组连续的FP寄存器传递参数。

　　子程序的返回结果为一个32位整数时，通过r0返回；返回结果为一个64位整数时，通过r0和r1返回；依此类推。结果为浮点数时，通过浮点运算部件的寄存器F0、D0或者S0返回。

# 三、汇编调用C函数

1. 汇编程序的书写要遵循ATPCS规则，以保证程序调用时正确的**参数传递**
2. 通过**BL指令**来**调用C函数**

示例：

```c
int add(int x,int y)
{
	return(x+y);
}
```

```assembly
@……
MOV r0,1
MOV r1,2
BL add ;调用C函数add
@……
```

# 四、C中调用汇编子程序

1. C程序调用汇编程序时，汇编程序的书写也要遵循ATPCS规则，以保证程序调用时正确的参数传递。
2. 在汇编程序中使用**.global伪操作**来**声明被调用的子程序**，表示该子程序将在其他文件中被调用
3. 在C程序中使用**extern关键字**来**声明要调用的汇编子程序为外部函数**

示例：

```assembly
……
.global add
add: @求和子程序add
ADD r0,r0,r1
MOV pc,lr @BX LR

```

```c
extern int add (int x,int y); //声明add为外部函数
 
void main()
{
	int a=1,b=2,c;
	c=add(a,b); //调用add子程序
	...
}
```

# 五、基本的内联汇编

GNU的C编译器使用asm关键字指出使用汇编语言编写的源代码段落。基本格式：
`asm volatile("assembly code":::);`
括号中的汇编格式：指令必须在引号里；指令超过一条，必须使用新行字符分隔

例如：

`asm volatile("swi 1\n\t":::);`

asm volatile("swi 2\n\t"

​							"swi 3\n\t":::)

如何将数据传递和传出汇编语言呢？一种方法是使用C语言的全局变量，并且只有全局的变量才能在基本的内联汇编代码内使用。

必须注意不改变任何寄存器的值



# 六、扩展的内联汇编(参考资料)

```c
__asm__　__volatile__(
	"Instruction List" 
	:Output Operand List
	:Input Operand List
	:Clobber/Modify List
);
```

```c
#include <stdio.h>  
 
int main(int argc, char **argv)  
{    
	int in = 100;   
	int out;  
 
   	__asm__ __volatile__(  
		"mov r0, %[input]\n"     
		"mov %[output], r0\n" 
		:[output]"=r"(out)    
		:[input]"r"(in)    
		:"r0"   
	);     
 
	printf("out = %d\n", out); 
 
	return 0;  
} 
```

1. \_\_asm\_\_是GCC 关键字asm 的宏定义。\_\_asm\_\_或asm用来声明一个内联汇编表达式，所以任何一个内联汇编表达式都是以它开头的，是必不可少的。`#define __asm__ asm`  
2.  \_\_volatile\_\_是GCC 关键字volatile 的宏定义。\_\_volatile\_\_或volatile 是可选的。如果用了它，则是向GCC 声明不允许对该内联汇编优化，否则当使用了优化选项(-O)进行编译时，GCC 将会根据自己的判断决定是否将这个内联汇编表达式中的指令优化掉`#define __volatile__ volatile`
3. "Instruction List"是指令列表。每条指令都必须被双引号括起来；两条指令必须用换行"\n"或分号";"分开。
4. Output Operand List用来指定当前内联汇编语句的输出操作符列表。每一个输出操作符都由3个部分组成：方括号[]中的符号名，限制字符串"=r"，圆括号()中的C表达式构成。输出操作符之间用逗号"，"分割。即:[out1]"=r"(value1), [out2]"=r"(value2), ... [outn]"=r"(valuen)
5. Input Operand List用来指定当前内联汇编语句的输入操作符列表。表示方法同上。即:[in1]"=r"(value1), [in2]"=r"(value2), ... [inn]"=r"(valuen)
6. Clobber/Modify List通知GCC当前内联汇编语句可能会对某些寄存器或内存进行修改，希望GCC在编译时能够将这一点考虑进去。这种情况一般发生在一个寄存器出现在"Instruction List"，但却不是由Input/Output操作表达式所指定的，也不是在一些Input/Output操作表达式使用"r"约束时由GCC为其选择的，同时此寄存器被"Instruction List"中的指令修改，而这个寄存器只是供当前内联汇编临时使用的情况。如果一个内联汇编语句的Clobber/Modify域存在"memory"，那么GCC会保证在此内联汇编之前，如果某个内存的内容被装入了寄存器，那么在这个内联汇编之后，如果需要使用这个内存处的内容，就会直接到这个内存处重新读取，而不是使用被存放在寄存器中的拷贝。因为这个时候寄存器中的拷贝已经很可能和内存处的内容不一致了。

```c
__asm__　__volatile__(
	"Instruction 1\n"
	"Instruction 2\n"
	...
	"Instruction n\n"
	:[out1]"=r"(value1), [out2]"=r"(value2), ... [outn]"=r"(valuen)
	:[in1]"=r"(value1), [in2]"=r"(value2), ... [inn]"=r"(valuen)
	:"r0", "r1", ... "rn"
);

```

限制字符串表：

![限制字符表](.\限制字符表.jpg)

限制字符可能要单个修饰符指示。要是没有修饰符指示的默认为只读操作符

![限制字符的修饰符](.\限制字符的修饰符.jpg)