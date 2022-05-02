all:
	arm-none-linux-gnueabi-gcc -c rtc.c uart.c start.s
	arm-none-linux-gnueabi-ld -Ttext 0x40008000 start.o rtc.o uart.o -o rtc.elf
	arm-none-linux-gnueabi-objcopy -O binary -S rtc.elf rtc.bin
clean:
	rm -f *.o *.elf *.bin
