; Hexa OS Bootloader
[org 0x7c00]
bits 16

start:
    mov si, msg
    call print_string
    jmp $

print_string:
    mov ah, 0x0E
.loop:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .loop
.done:
    ret

msg db "Welcome to Hexa OS - Booting...", 0

times 510 - ($ - $$) db 0
dw 0xAA55
