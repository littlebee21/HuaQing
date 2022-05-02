all:
	arm-none-linux-gnueabi-gcc -c int.c start.s
	arm-none-linux-gnueabi-ld -Ttext 0x40008000 start.o int.o -o int.elf
	arm-none-linux-gnueabi-objcopy -O binary -S int.elf int.bin
clean:
	rm -f *.o *.elf *.bin
