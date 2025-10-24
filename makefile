all: hexaos.bin

hexaos.bin: boot/boot.asm
	nasm -f bin boot/boot.asm -o hexaos.bin
