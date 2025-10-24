#include <stdint.h>
#include "drivers/io.h"

// Forward declarations of external functions
extern void idt_init();
extern void keyboard_handler();
extern void mouse_handler();
extern void timer_init(uint32_t freq);

// VGA text mode base address
#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// VGA colors
#define WHITE_ON_BLACK 0x0F
#define RED_ON_BLACK 0x0C
#define CYAN_ON_BLACK 0x0B

// Function to print text to screen
static volatile uint16_t* vga_buffer = (uint16_t*)VGA_ADDRESS;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

void clear_screen() {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga_buffer[i] = (uint16_t)' ' | (WHITE_ON_BLACK << 8);
    cursor_x = 0;
    cursor_y = 0;
}

void print(const char* str, uint8_t color) {
    if (!color) color = WHITE_ON_BLACK;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            vga_buffer[cursor_y * VGA_WIDTH + cursor_x] =
                (uint16_t)str[i] | (color << 8);
            cursor_x++;
        }
        if (cursor_x >= VGA_WIDTH) {
            cursor_x = 0;
            cursor_y++;
        }
        if (cursor_y >= VGA_HEIGHT) {
            cursor_y = 0;
        }
    }
}

// Initialize devices
void init_devices() {
    idt_init();
    timer_init(50); // 50Hz PIT frequency
    print("[OK] IDT & Timer Initialized\n", CYAN_ON_BLACK);
    print("[OK] Keyboard Ready\n", CYAN_ON_BLACK);
    print("[OK] Mouse Ready\n", CYAN_ON_BLACK);
}

// Kernel main entry point
void kernel_main() {
    clear_screen();
    print("Hexa OS v0.1 (64-bit Kernel)\n", RED_ON_BLACK);
    print("----------------------------------------\n", WHITE_ON_BLACK);
    print("Initializing system components...\n\n", WHITE_ON_BLACK);

    init_devices();

    print("\nSystem ready. Welcome to Hexa OS!\n", WHITE_ON_BLACK);
    print("Press keys or move the mouse to test input.\n", WHITE_ON_BLACK);

    // Infinite loop — halts CPU until interrupt
    while (1) {
        __asm__ volatile("hlt");
    }
}
