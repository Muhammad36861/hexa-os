; boot/boot64.asm
BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Load kernel (sectors 2–)
    mov bx, 0x1000
    mov dh, 10
    call load_kernel

    ; Enable A20
    in al, 0x92
    or al, 2
    out 0x92, al

    ; Set up GDT for protected mode
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODE_SEG:init_pm

[BITS 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x90000

    ; Enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 0x00000100
    wrmsr

    ; Enable paging
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    mov eax, pml4_table
    mov cr3, eax

    mov eax, cr0
    or eax, (1 << 31)
    mov cr0, eax

    jmp 0x08:init_long

[BITS 64]
init_long:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax

    call kernel_start64
    hlt
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
    dq 0
    dq 0x00AF9A000000FFFF
    dq 0x00AF92000000FFFF
gdt_descriptor:
    dw gdt_descriptor - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

align 4096
pml4_table:
    dq pdpt_table | 0x03
align 4096
pdpt_table:
    dq pd_table | 0x03
align 4096
pd_table:
    dq 0x0000000000000083
    times 511 dq 0

times 510-($-$$) db 0
dw 0xAA55
