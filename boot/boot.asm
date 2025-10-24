[org 0x7c00]
bits 16

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    ; Load kernel to memory 0x1000
    mov bx, 0x1000
    mov dh, 2
    call load_kernel

    ; Jump to protected mode
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:init_pm

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000

    call KERNEL_START

    jmp $

load_kernel:
    mov ah, 0x02
    mov al, dh
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [BOOT_DRIVE]
    int 0x13
    ret

BOOT_DRIVE db 0

gdt_start:
    dq 0x0000000000000000
    dq 0x00cf9a000000ffff
    dq 0x00cf92000000ffff

gdt_descriptor:
    dw gdt_descriptor - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10
KERNEL_START equ 0x1000

times 510-($-$$) db 0
dw 0xaa55
