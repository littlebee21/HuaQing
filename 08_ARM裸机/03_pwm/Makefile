all:
	arm-none-linux-gnueabi-gcc -c pwm.c start.s
	arm-none-linux-gnueabi-ld -Ttext 0x40008000 start.o pwm.o uart.o -o pwm.elf
	arm-none-linux-gnueabi-objcopy -O binary -S pwm.elf pwm.bin
clean:
	rm -f *.o *.elf *.bin
