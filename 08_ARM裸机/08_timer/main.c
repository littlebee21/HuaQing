#include "key.h"
#include "timer.h"
void delay_ms(unsigned int mm)
{
	int i = 0,j = 0;
	for (i = 0;i < mm;i++)
		for(j = 0;j < 2200;j++);
}
int main()
{
	key_gpio_init(); 
	key_gic_init();
	GPX1.CON = GPX1.CON & (~(0xF << 0)) | (0x1 << 0);  // led3 
	timer_init();
	timer_gic_init();
	
	while(1)
	{
	
		// 按键按下，触发按键中断	
	}
	return 0;
}
