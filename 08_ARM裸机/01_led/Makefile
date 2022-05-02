all:
	arm-none-linux-gnueabi-gcc -c led.c start.s
	arm-none-linux-gnueabi-ld -Ttext 0x40008000 start.o led.o -o led.elf
	arm-none-linux-gnueabi-objcopy -O binary -S led.elf led.bin
clean:
	rm -f *.o *.elf *.bin
