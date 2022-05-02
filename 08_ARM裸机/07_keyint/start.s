.text
.global _start
_start:
		b		reset
		b .
		b .
		b .
		b .
		b .
		ldr		pc,_irq
		b . /*发生fiq时会跳转到这里*/
/*为什么FIQ处理起来,会比较快,1.优先级高 2.处理程序可以不用跳转 3.FIQ模式有很多私有的寄存器 不用保存和恢复*/


_irq:					.word  irq_handler

reset:

	ldr	r0,=0x40008000
	mcr	p15,0,r0,c12,c0,0		@ Vector Base Address Register
	
	msr cpsr,#0x12 
	ldr sp,=stack_end
	
	msr	cpsr,#0x13
	bl	main
	b .

irq_handler:
	sub  lr,lr,#4
	stmfd sp!,{r0-r12,lr}
	bl	do_irq
	ldmfd sp!,{r0-r12,pc}^

.data
stack:
	.space 1024,0
stack_end:
.end

