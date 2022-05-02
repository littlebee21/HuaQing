
#define GPD0CON (*(volatile unsigned int*)0x114000a0)

#define TCFG0 (*(volatile unsigned int*)0x139d0000)
#define TCFG1 (*(volatile unsigned int*)0x139d0004)
#define TCON (*(volatile unsigned int*)0x139d0008)
#define TCNTB0 (*(volatile unsigned int*)0x139d000c)
#define TCMPB0 (*(volatile unsigned int*)0x139d0010)

unsigned char uart_getc();
void uart_putc(unsigned char c);
void uart_putc(unsigned char c);
void uart_init(void);

void pwm_init(int f,int t)
{
	//设置计数频率
	GPD0CON = (GPD0CON &(~(0xf))) | 0x2; //将GPD0_0设为TOUT_0,也就PWM脉冲输出方式
	TCFG0 = (TCFG0 & (~0xff)) | 0x63; //将100M分频为1M 100M/(99+1)
	TCFG1 = (TCFG1 & (~0xf)) | 3; //将频率将除以8
	//确定周期和占空比
	TCNTB0 = f; //确定周期(频率)
	TCMPB0 = t; //确定占空比50%
	//刷新与生效
	TCON = (TCON &(~0xf)) | 0xa; //当修改了TCNTB0与TCMPB0后,需要刷新与重新启动PWM
	TCON = (TCON & ~0xf) | 9;
}

void pwm_update_t(int f,int t)
{
	TCNTB0 = f;
	TCMPB0 = t;
	TCON = (TCON &(~0xf)) | 0xa; //当修改了TCNTB0与TCMPB0后,需要刷新与重新启动PWM
	TCON = (TCON & ~0xf) | 9;
}

int main()
{
	int i=200;
	
	uart_init();
	pwm_init(i,i/2);
	
	uart_puts("hello world\r\n");
	
	while(1)
	{
		unsigned char ch=uart_getc();
		if(ch == 'a')
		{
			uart_putc(ch);
			i++;
			pwm_update_t(i,i/2);
		}
		else if(ch == 'b')
		{
			uart_putc(ch);
			i--;
			if(i<2)
				i=2;
			pwm_update_t(i,i/2);
		}
	}
	return 0;
}

