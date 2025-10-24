ASM = nasm
CC = i686-elf-gcc
LD = i686-elf-ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -Ttext 0x1000 --oformat binary

all: hexaos.bin

boot.bin: boot/boot.asm
	$(ASM) $< -f bin -o $@

kernel.bin: kernel/kernel.c
	$(CC) $(CFLAGS) -c $< -o kernel.o
	$(LD) $(LDFLAGS) kernel.o -o kernel.bin

hexaos.bin: boot.bin kernel.bin
	cat boot.bin kernel.bin > hexaos.bin

run: hexaos.bin
	qemu-system-x86_64 -drive format=raw,file=hexaos.bin

clean:
	rm -f *.bin *.o
