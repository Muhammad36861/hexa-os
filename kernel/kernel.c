#include <stdint.h>

#define VGA_WIDTH 320
#define VGA_HEIGHT 200
#define VGA_ADDRESS 0xA0000

void putpixel(int x, int y, uint8_t color) {
    uint8_t* VGA = (uint8_t*)VGA_ADDRESS;
    VGA[(y * VGA_WIDTH) + x] = color;
}

void clear_screen(uint8_t color) {
    for (int y = 0; y < VGA_HEIGHT; y++)
        for (int x = 0; x < VGA_WIDTH; x++)
            putpixel(x, y, color);
}

void draw_rect(int x, int y, int w, int h, uint8_t color) {
    for (int j = y; j < y + h; j++)
        for (int i = x; i < x + w; i++)
            putpixel(i, j, color);
}

void kernel_main(void) {
    clear_screen(1); // Blue background (like Win10)
    
    // Taskbar
    draw_rect(0, VGA_HEIGHT - 20, VGA_WIDTH, 20, 8);

    // Start button
    draw_rect(5, VGA_HEIGHT - 18, 35, 16, 2);

    // “Start” text (simple placeholder)
    uint8_t* text = (uint8_t*)0xB8000;
    const char* msg = "Hexa OS";
    for (int i = 0; msg[i] != 0; i++) {
        text[i * 2] = msg[i];
        text[i * 2 + 1] = 0x0F;
    }

    for (;;) ;
}
