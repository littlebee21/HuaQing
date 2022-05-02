all:
	arm-none-linux-gnueabi-gcc -c adc.c start.s
	arm-none-linux-gnueabi-ld -Ttext 0x40008000 start.o adc.o uart.o -o adc.elf
	arm-none-linux-gnueabi-objcopy -O binary -S adc.elf adc.bin
clean:
	rm -f *.o *.elf *.bin
