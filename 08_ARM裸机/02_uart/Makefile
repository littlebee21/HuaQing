all:
	arm-none-linux-gnueabi-gcc -c uart.c start.s
	arm-none-linux-gnueabi-ld -Ttext 0x40008000 start.o uart.o -o uart.elf
	arm-none-linux-gnueabi-objcopy -O binary -S uart.elf uart.bin
clean:
	rm -f *.o *.elf *.bin
