all:
	arm-none-linux-gnueabi-gcc -c key.c start.s
	arm-none-linux-gnueabi-ld -Ttext 0x40008000 start.o key.o -o key.elf
	arm-none-linux-gnueabi-objcopy -O binary -S key.elf key.bin
clean:
	rm -f *.o *.elf *.bin
