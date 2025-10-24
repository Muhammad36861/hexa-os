all: hexaos.bin

boot/boot64.o: boot/boot64.asm
	nasm -f bin boot/boot64.asm -o boot/boot64.o

kernel/kernel.o: kernel/kernel.c
	x86_64-elf-gcc -ffreestanding -m64 -c kernel/kernel.c -o kernel/kernel.o

hexaos.bin: boot/boot64.o kernel/kernel.o linker.ld
	x86_64-elf-ld -T linker.ld -o hexaos.elf kernel/kernel.o
	cat boot/boot64.o hexaos.elf > hexaos.bin

run:
	qemu-system-x86_64 -drive format=raw,file=hexaos.bin

clean:
	rm -f *.o *.bin *.elf
