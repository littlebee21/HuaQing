#define  (*(volatile unsigned int*)0x10070040)
#define BCDYEAR (*(volatile unsigned int*)0x10070088)
#define BCDMON (*(volatile unsigned int*)0x10070084)
#define BCDDAY (*(volatile unsigned int*)0x1007007c)
#define BCDDAYWEEK (*(volatile unsigned int*)0x10070080)
#define BCDHOUR (*(volatile unsigned int*)0x10070078)
#define BCDMIN (*(volatile unsigned int*)0x10070074)
#define BCDSEC (*(volatile unsigned int*)0x10070070)


unsigned char uart_getc();
void uart_putc(unsigned char c);
void uart_puts(const char *str);

void delay(int d)
{
	int i,j;
	while(d--)
	{
		for(i=0;i<5;i++)
			for(j=0;j<500;j++)
				;
	}
}


void rtc_init(void)
{
	RTCCON = 1; //设置之前,打开可以设置的开关

	BCDYEAR = 0x020; //设置年
	BCDMON = 0x04; //设置月
	BCDDAY = 0x03; //设置日期
	BCDDAYWEEK = 0x5; //设置星期几
	BCDHOUR = 0x10; //设置小时
	BCDMIN = 0x03; //设置分
	BCDSEC = 0x55; //设置秒
	
	RTCCON = 0; //关闭开关,防止意外修改,刷新,因为值发生了变化
}

int main()
{
	rtc_init(); //初始化rtc,也就是设置年月日时分秒
	uart_puts("print time\r\n");
	while(1)
	{
		//显示2020
		uart_putc('2');
		uart_putc(((BCDYEAR>>8) &0xf) +'0');
		uart_putc(((BCDYEAR>>4) &0xf) +'0');
		uart_putc((BCDYEAR &0xf) +'0');
		uart_putc('-');
		//显示月
		uart_putc(((BCDMON>>4) &0xf) +'0');
		uart_putc((BCDMON &0xf) +'0');
		uart_putc('-');
		//显示日期
		uart_putc(((BCDDAY>>4) &0xf) +'0');
		uart_putc((BCDDAY &0xf) +'0');
		uart_puts("    ");
		uart_putc(((BCDHOUR>>4) &0xf) +'0');
		uart_putc((BCDHOUR &0xf) +'0');
		uart_putc(':');
		uart_putc(((BCDMIN>>4) & 0xf) +'0');
		uart_putc((BCDMIN & 0xf) +'0');
		uart_putc(':');
		uart_putc(((BCDSEC>>4) & 0xf) +'0');
		uart_putc((BCDSEC & 0xf) +'0');
		uart_puts("     week:");
		uart_putc((BCDDAYWEEK & 0xf)+'0');

		uart_puts("\r\n");
		delay(1000);
	}
	return 0;
}

