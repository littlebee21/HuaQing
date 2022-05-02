#define GPF3CON (*(volatile unsigned int*)0x114001e0)
#define GPF3DAT (*(volatile unsigned int*)0x114001e4)
#define GPX1CON (*(volatile unsigned int*)0x11000c20)
#define GPX1DAT (*(volatile unsigned int*)0x11000c24)
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

//这个函数让4个LED灯都熄灭
void led_off(void)
{
	GPX2DAT &= ~(1<<7);
	GPX1DAT &= ~(1<<0);
	GPF3DAT &= ~(1<<4);
	GPF3DAT &= ~(1<<5);
}

//这个函数让第i个灯亮
void led_on(int i)
{
	switch(i)
	{
	case 2:
		GPX2DAT |= (1<<7);
		break;
	case 3:
		GPX1DAT |= (1<<0);
		break;
	case 4:
		GPF3DAT |= (1<<4);
		break;
	case 5:
		GPF3DAT |= (1<<5);
		break;
	}
}

int main()
{
	int i=2; //i代表哪一个LED灯是亮的
	GPF3CON = GPF3CON &(~(0xf<<20)) | (0x1<<20); //让GPF3_5是输出功能
	GPF3CON = GPF3CON &(~(0xf<<16)) | (0x1<<16); //让GPF3_4是输出功能
	GPX1CON = GPX1CON &(~0xf) | (0x1); //让GPX1_0是输出功能
	GPX2CON = GPX2CON &(~(0xf<<28)) | (0x1<<28); //让GPX2_7是输出功能

	GPX1CON = GPX1CON &(~(0xf<<4)); //让GPX1_1是输入功能
	GPX1CON = GPX1CON &(~(0xf<<8)); //让GPX1_2是输入功能
	led_on(i); //让LED2点亮
	while(1)
	{
		if((GPX1DAT & (1<<1))==0) //判断k2是否被按下,如果被按下,结果为true
		{
			i++;
			if(i>5)
				i=2;
			led_off();
			led_on(i);
			delay(500);
		}
		if((GPX1DAT & (1<<2))==0) //判断k3是否被按下,如果被按下,结果为true
		{
			i--;
			if(i<2)
				i=5;
			led_off();
			led_on(i);
			delay(500);
		}
	}
	return 0;
}

