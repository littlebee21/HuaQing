# 一、start.s

```asm
.text
.globl _start
_start:
	bl main
.end
```

# 二、led.c

```c
#define GPX2CON (*(volatile unsigned int*)0x11000c40)
#define GPX2DAT (*(volatile unsigned int*)0x11000c44)

void delay(int d)
{
	int i,j;
	while(d--)
	{
		for(i=0;i<5;i++)
			for(j=0;j<514;j++)
				;

	}
}

int main()
{
	GPX2CON = GPX2CON &(~(0xf<<28)) | (0x1<<28); //让GPX2_7是输出功能
	while(1)
	{
		GPX2DAT |= (1<<7); //让GPX2_7输出高电平,点亮LED2
		delay(1000);
		GPX2DAT &= ~(1<<7); //让GPX2_7输出低电平,熄灭LED2
		delay(1000);
	}
	return 0;
}

```



# 三、原理解析

led原理图

![led原理图](.\led原理图.jpg)

根据原理图得知：

1. LED2 使用GPIO口GPX2_7
2. 该引脚高电平时LED2亮，低电平时LED2灭
3. 芯片向LED2电路输出电平，因此该引脚应该配置成输出功能



查阅芯片手册中关于GPX2组的寄存器地址（见6.2.3.202和6.2.3.203）

![GPX2_7寄存器](.\GPX2_7寄存器.jpg)

其它三个led灯原理雷同与led2，只是相应的寄存器地址不一样，操作的寄存器对应位不一样





LED2 GPX2_7  con-0x11000c40-[28,31]  dat-0x11000c44-[7]

LED3 GPX1_0 con-0x11000c20-[0,3] dat-0x11000c24-[0]

LED4 GPF3_4 con-0x114001e0-[16,19] dat-0x114001e4-[4] 

LED5 GPF3_5 con-0x114001e0-[20,23] dat-0x114001e4-[5] 

