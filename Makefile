#/*
#* Platform  for: allwiner  A10
#* author  by jiangdou
#* time  at: 2012-0801
#*
#*
#*/


uart.bin:start.S main.c uart.c clock.c lib.c
	arm-linux-gnueabihf-gcc -nostdlib -c start.S -o start.o
	arm-linux-gnueabihf-gcc -nostdlib -c main.c -o main.o
	arm-linux-gnueabihf-gcc -nostdlib -c uart.c -o uart.o
	arm-linux-gnueabihf-gcc -nostdlib -c lib.c -o lib.o
	arm-linux-gnueabihf-gcc -nostdlib -c clock.c -o clock.o
	arm-linux-gnueabihf-ld -Ttext 0x00000020 start.o main.o uart.o lib.o clock.o  -o uart_elf
	arm-linux-gnueabihf-objcopy -O binary -S uart_elf uart.bin
clean:
	rm -rf *.o *.bin uart_elf *.dis

