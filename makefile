TARGET = hexa
ISO    = $(TARGET).iso
KERNEL = kernel.bin
CC = gcc
AS     = nasm
LD     = x86_64-elf-ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra -m64 -nostdlib
LDFLAGS = -T linker.ld -nostdlib

SRC = $(wildcard kernel/*.c kernel/drivers/*.c)
OBJ = $(SRC:.c=.o) boot/boot.o

all: $(ISO)

boot/boot.o: boot/boot64.asm
	$(AS) -f elf64 $< -o $@

$(KERNEL): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

$(ISO): $(KERNEL)
	mkdir -p iso/boot/grub
	cp $(KERNEL) iso/boot/$(KERNEL)
	echo 'set timeout=0'                      >  iso/boot/grub/grub.cfg
	echo 'set default=0'                      >> iso/boot/grub/grub.cfg
	echo 'menuentry "Hexa OS" { multiboot2 /boot/$(KERNEL) }' >> iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) iso

clean:
	rm -rf $(OBJ) $(KERNEL) $(ISO) iso

run: all
	qemu-system-x86_64 -cdrom $(ISO)
