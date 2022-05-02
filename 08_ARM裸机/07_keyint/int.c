#define UTXH2 (*((volatile unsigned int*)0x13820020))
#define URXH2 (*((volatile unsigned int*)0x13820024))
#define UTRSTAT2 (*((volatile unsigned int*)0x13820010))

void uart_putc(unsigned char data)
{
	while((UTRSTAT2 &(1<<1))==0);
	UTXH2=data;
}

unsigned char uart_getc(void)
{
	while((UTRSTAT2 & (1<<0))==0);
	return URXH2;
}

void uart_puts(const char *str)
{
	while(*str)
	{
		uart_putc(*str);
		str++;
	}
}

#define ICCICR_CPU0 (*(volatile unsigned int*)0x10480000)
#define ICDISER1_CPU0 (*(volatile unsigned int*)0x10490104)
#define ICCPMR_CPU0 (*(volatile unsigned int*)0X10480004)
#define ICDDCR (*(volatile unsigned int*)0x10490000)
#define ICDIPTR14_CPU0 (*(volatile unsigned int*)0x10490838)
#define ICCIAR_CPU0 (*(volatile unsigned int*)0x1048000c)
#define ICDICPR1 (*(volatile unsigned int*)0x10490284)
#define ICCEOIR_CPU0 (*(volatile unsigned int*)0x10480010)
#define EXT_INT41_PEND (*(volatile unsigned int*)0x11000f44)
#define EXT_INT41_CON (*(volatile unsigned int*)0x11000e04)
#define EXT_INT41_MASK (*(volatile unsigned int*)0x11000f04)
#define GPX1CON (*(volatile unsigned int*)0x11000c20)
#define GPX1PUD (*(volatile unsigned int*)0x11000c28)
void do_irq(void )
{
	int irq_num;
	//从ICCIAR_CPU0中读取中断ID号
	irq_num = (ICCIAR_CPU0 & 0x3FF);
	switch (irq_num) {

	case 58: //k3被按下
		uart_puts("SPI26\r\n");

		//清GPIO控制器中断挂起位
		EXT_INT41_PEND |= 0x1 << 2;
		//GIC中断状态清除寄存器,每位对应一个中断,当中断发生时自动置1,标识中断发生,当中断处理完毕后,需要软件写1清0
		ICDICPR1 |= 1<< 26;
		break;
	case 57: //k2被按下
		uart_puts("SPI25\r\n");

		//清GPIO控制器中断挂起位
  		EXT_INT41_PEND |= 0x1 << 1;
		//GIC中断状态清除寄存器,每位对应一个中断,当中断发生时自动置1,标识中断发生,当中断处理完毕后,需要软件写1清0
		ICDICPR1 |= 1<< 25;
		break;
	}

	//当中断处理程序结束后,需要将处理的中断ID号写入ICCEOIR,作为ARM核心给GIC控制器的结束信号
	ICCEOIR_CPU0 = (ICCEOIR_CPU0 & ~(0x3FF)) | irq_num;

}

int main(void)
{
	//GPIO级
	//Key_2  Interrupt  GPX1_1
	GPX1PUD = GPX1PUD & ~(0x3 << 2); // Disables Pull-up/Pull-down
	GPX1CON = (GPX1CON & ~(0xF << 4)) | (0xF << 4); //GPX1_1: WAKEUP_INT1[1](EXT_INT41[1])
	EXT_INT41_CON = (EXT_INT41_CON & ~(0x7 << 4)) | 0x2 << 4;
	EXT_INT41_MASK = (EXT_INT41_MASK & ~(0x1 << 1)); //  Bit: 1 = Enables interrupt

	//Key_3  Interrupt  GPX1_2
	GPX1PUD = GPX1PUD & ~(0x3 << 4); // Disables Pull-up/Pull-down
	GPX1CON = (GPX1CON & ~(0xF << 8)) | (0xF << 8); //GPX1_2:WAKEUP_INT1[2] (EXT_INT41[2])
	EXT_INT41_CON = (EXT_INT41_CON & ~(0x7 << 8)) | 0x2 << 8;
	EXT_INT41_MASK = (EXT_INT41_MASK & ~(0x1 << 2)); //  Bit: 1 = Enables interrupt


	//CPU级
	ICDISER1_CPU0= (1<<25) | (1<<26); //中断使能寄存器,使能SPI25和SPI26
	//中断目标CPU配置寄存器,配置将中断发送到哪个CPU处理,每个中断用8位来配置它的目标CPU,每位对应1个CPU
	ICCICR_CPU0 = 1; //CPU0的中断通道全局使能 0:禁止 1:使能
	ICCPMR_CPU0 = 255; //CPU优先级过滤寄存器 中断屏蔽级别0~255
	
	//GIC级初始化
	ICDIPTR14_CPU0 = 0x00010100; //SPI25 SPI26中断发送到CPU0处理
	ICDDCR = 1; //GIC中断使能寄存器 0:禁止 1:使能
	
	uart_puts("interrupt test\r\n");
	while (1){
		uart_putc(uart_getc()); //可以测试程序是否正在执行
	}

	return 0;
}
