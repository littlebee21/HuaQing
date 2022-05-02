#include "timer.h"
void timer_init(void) 
{
	// 2. 设置PWM的一级分频值，进行250分频   TCFG0[7:0] = 249
	PWM.TCFG0 = PWM.TCFG0 & (~(0xFF)) | 249;
	// 3. 设置PWM的二级分频值，进行4分频     TCFG1[3:0] = 2
	PWM.TCFG1 = PWM.TCFG1 & (~(0xF)) | 0x2;
	// 4. 设置TCNTB0的初始值，确定PWM方波的周期   TCNTB0[31:0] = 99
	PWM.TCNTB0 = 100000-1;	
	// 6. 打开手动加载  TCON[1] = 1
	PWM.TCON |= (0x1 << 1);
	// 7. 打开自动加载  TCON[3] = 1
	PWM.TCON |= (0x1 << 3);
	// 8. 关闭手动加载  TCON[1] = 0
	PWM.TCON &= (~(0x1 << 1));
	// 9. 开启PWM定时器 TCON[0] = 1
	PWM.TCON |= 0x1;
	// 10. 使能PWM定时器的中断功能 
	PWM.TINT_CSTAT |= 0x1;
}
void timer_gic_init(void)
{
	// timer -- > 中断号69   SPI37
	// GICD 
	// 1. 设置分配器层中断使能位  ICDISER2_CPU0[5] = 0x1 
	ICDISER.ICDISER2 |= (0x1 << 5);

	// 2. 设置分配器层中断优先级设置寄存器 ICDIPR17_CPU0[15:8] = 69
	ICDIPR.ICDIPR17 = ICDIPR.ICDIPR17 & (~(0xFF << 8)) | (69 << 8);

	// 3. 设置分配器层中断目标分配寄存器   ICDIPTR17_CPU0[15:8] = 0x1
	ICDIPTR.ICDIPTR17 = ICDIPTR.ICDIPTR17 & (~(0xFF << 8)) | (0x1 << 8);

	// 4. 设置分配器层中断全局使能寄存器   ICDDCR[0] = 0x1
	ICDDCR |= 0x1;

	// GICC
	// 5. 设置CPU接口层中断全局使能寄存器   ICCICR_CPU0[0] = 0x1 
	CPU0.ICCICR |= 0x1;

	// 6. 设置CPU接口层中断屏蔽寄存器       ICCPMR_CPU0[7:0] = 100
	CPU0.ICCPMR = 100;
}
