#include "key.h"
void key_gpio_init(void) 
{
	// 1. 设置GPX1_1引脚为中断功能  GPX1CON[7:4] = 0xF
	GPX1.CON = GPX1.CON | (0xF << 4);
	// 2. 设置GPX1_1引脚为下降沿触发中断  EXT_INT41CON[6:4] = 0x2
	EXT_INT41_CON = EXT_INT41_CON & (~(0x7 << 4)) | (0x2 << 4);
	// 3. 设置GPX1_1引脚中断使能位    EXT_INT41MASK[1] = 0x0
	EXT_INT41_MASK = EXT_INT41_MASK & (~(0x1 << 1));
}

void key_gic_init(void)
{
	// GICD 
	// 1. 设置分配器层中断使能位  ICDISER1_CPU0[25] = 0x1 
	ICDISER.ICDISER1 |= (0x1 << 25);
	// 2. 设置分配器层中断优先级设置寄存器 ICDIPR14_CPU0[15:8] = 57
	ICDIPR.ICDIPR14 = ICDIPR.ICDIPR14 & (~(0xFF << 8)) | (57 << 8);
	// 3. 设置分配器层中断目标分配寄存器   ICDIPTR12_CPU0[15:8] = 0x1
	ICDIPTR.ICDIPTR14 = ICDIPTR.ICDIPTR14 & (~(0xFF << 8)) | (0x1 << 8);
	// 4. 设置分配器层中断全局使能寄存器   ICDDCR[0] = 0x1
	ICDDCR |= 0x1;
	// GICC
	// 5. 设置CPU接口层中断全局使能寄存器   ICCICR_CPU0[0] = 0x1 
	CPU0.ICCICR |= 0x1;
	// 6. 设置CPU接口层中断屏蔽寄存器       ICCPMR_CPU0[7:0] = 100
	CPU0.ICCPMR = 100;
}
