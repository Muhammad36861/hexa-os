ASM = nasm
CC = x86_64-elf-gcc
LD = x86_64-elf-ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra -m64 -nostdlib

all: hexaos64.bin

boot.bin: boot/boot64.asm
	$(ASM) $< -f bin -o $@

kernel.bin: kernel/kernel64.c
	$(CC) $(CFLAGS) -c $< -o kernel.o
	$(LD) -T linker.ld -o kernel.elf kernel.o
	objcopy -O binary kernel.elf kernel.bin

hexaos64.bin: boot.bin kernel.bin
	cat boot.bin kernel.bin > hexaos64.bin

run: hexaos64.bin
	qemu-system-x86_64 -drive format=raw,file=hexaos64.bin

clean:
	rm -f *.bin *.o *.elf
