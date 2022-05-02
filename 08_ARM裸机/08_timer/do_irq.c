#include "exynos_4412.h"
void do_irq(void) 
{
	// 中断处理程序
	int irq_num;
	// 1. 获取中断号    读ICCIAR[9:0]
	irq_num = CPU0.ICCIAR & 0x3FF;
	switch (irq_num) {
		case 57:
			// led灯交替亮灭的代码	
			GPX1.DAT = GPX1.DAT ^ (1 << 0); 		// led3
			printf("k2 key!");
			// 2. 清除GPIO层的中断挂起标志位    EXT_INT41PEND[1] = 0x1
			EXT_INT41_PEND |= (0x1 << 1);
			// 3. 清除分配器层的中断挂起标志位  ICDICPR1_CPU0[25] = 0x1 
			ICDICPR.ICDICPR1 |= (0x1 << 25);
			break;
		case 58:
			break;
		case 69:
			printf("1s timer interrupt\n");
			// 清除PWM层中断 
			PWM.TINT_CSTAT |= (1 << 5);
			// 3. 清除分配器层的中断挂起标志位  ICDICPR2_CPU0[5] = 0x1 
			ICDICPR.ICDICPR2 |= (0x1 << 5);

			break;
		default:
			break;
	}
	// 4. 清除CPU接口层的中断号  ICCEOIR[9:0] = irq_num
	CPU0.ICCEOIR = CPU0.ICCEOIR & (~(0x3FF)) | irq_num;

}
