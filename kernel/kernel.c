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

void kernel_main(void) {
    clear_screen(1); // Blue background
    // draw taskbar
    for (int y = 180; y < 200; y++)
        for (int x = 0; x < VGA_WIDTH; x++)
            putpixel(x, y, 8); // Gray taskbar

    // start button
    for (int y = 182; y < 198; y++)
        for (int x = 5; x < 45; x++)
            putpixel(x, y, 2); // Green Start

    for(;;);
}
