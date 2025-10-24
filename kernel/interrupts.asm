; 64-bit IDT stub
[BITS 64]
global isr_stub_table
global load_idt

section .text
isr_stub_table:
%assign i 0
%rep 256
isr%+i:
    push qword i
    jmp isr_common
%assign i i+1
%endrep

isr_common:
    cli
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    mov rdi, rsp
    call isr_handler
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    add rsp, 8
    sti
    iretq

load_idt:
    lidt [rdi]
    ret
