// kernel/kernel.c
#include <stdint.h>

#define VGA_ADDR 0xB8000

void clear_screen() {
    uint16_t *vga = (uint16_t*)VGA_ADDR;
    for (int i = 0; i < 80*25; i++)
        vga[i] = 0x0720; // blank space with grey bg
}

void print(const char *s, int row) {
    volatile char *vga = (char*)VGA_ADDR + row * 160;
    while (*s) {
        *vga++ = *s++;
        *vga++ = 0x0F;
    }
}

void kernel_main() {
    clear_screen();
    print("Welcome to Hexa OS 64-bit Kernel", 0);
    print("Initializing subsystems...", 2);

    // TODO: memory_init(), load_drivers(), gui_init();
    for (;;) __asm__("hlt");
}
