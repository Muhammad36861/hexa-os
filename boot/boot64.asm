; boot/boot64.asm
[org 0x7c00]
bits 16

jmp start

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

    mov si, msg
    call print

    ; Enter 64-bit mode setup (we’ll extend later)
    hlt

print:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp print
.done:
    ret

msg db "Booting Hexa OS 64-bit...", 0

times 510-($-$$) db 0
dw 0xAA55
