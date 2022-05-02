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
		     //寄存器值    取高四位     置为0x01
	while(1)
	{
		GPX2DAT |= (1<<7); //让GPX2_7输出高电平,点亮LED2
		delay(1000);
		GPX2DAT &= ~(1<<7); //让GPX2_7输出低电平,熄灭LED2
		delay(1000);
	}
	return 0;
}

