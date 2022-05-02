
unsigned char uart_getc();
void uart_putc(unsigned char c);
void uart_puts(const char *str);

//将i的值转为字符串,存入buf i:0-4095
void myitoa(unsigned int i,char buf[5])
{
	buf[0]=i/1000+'0';
	i=i%1000;
    buf[1]=i/100+'0';
	i=i%100;
	buf[2]=i/10+'0';
	i=i%10;
	buf[3]=i+'0';
	buf[4]='\0';
}

//延时函数
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


#define ADC_CFG (*(volatile unsigned int*)0x10010118)
#define ADCMUX (*(volatile unsigned int*)0x126c001c)
#define ADCCON (*(volatile unsigned int*)0x126c0000)
#define ADCDAT (*(volatile unsigned int*)0x126c000c)

void ADC_init(void)
{
	ADC_CFG &= ~(1<<16); //将ADC_CFG的第16位清零,这样才能正常进行ADC转换
	ADCMUX = 3; //选择AIN3这一路模拟信号来进行ADC转换
	//读取结果后自动开始下一轮转换,频率100M/256,启动分频,ADC转换精度为12位
	ADCCON = (1<<16) | (1<<14) | (0xff<<6) | (1<<1);

	{
		unsigned int temp; //存放ADC转换的结果
		temp=ADCDAT&0xfff; //开始先随便读一次,以便启动ADC进行转换
	}
}

unsigned int ADC_read()
{
	unsigned int temp; //存放ADC转换的结果
	
	//等待ADC转换完成
	while((ADCCON & (1<<15))==0)
	{
		;	
	} 
	
	temp=ADCDAT & 0xfff; //转换完了,可以读取了,只低的12位有效

	//读取后,ADC会自动开始下一次转换
	
	return temp;		
}

int main()
{
	unsigned int temp;
	
	uart_init();
	
	ADC_init();

	while(1)
	{
		char buf[5]; //用来存放将二进制转成字符串后的字符串
		
		temp = ADC_read();
		
		myitoa(temp,buf); //将结果显示出来,我们要二进制数据转换为字符串
		
		uart_puts(buf); //只能打印字符串
		uart_puts("\r\n");
		delay(1000);
	}
	return 0;
}

