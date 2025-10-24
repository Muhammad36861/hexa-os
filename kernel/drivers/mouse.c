#include "../drivers/io.h"
#include <stdint.h>

#define MOUSE_DATA 0x60
#define MOUSE_STATUS 0x64
#define MOUSE_CMD 0x64
#define MOUSE_WRITE 0xD4

static int8_t packet[3];
static uint8_t packet_index = 0;
static int cursor_x = 40, cursor_y = 12;

void mouse_handler() {
    uint8_t status = inb(MOUSE_STATUS);
    while (status & 1) {
        int8_t data = inb(MOUSE_DATA);
        packet[packet_index++] = data;
        if (packet_index == 3) {
            packet_index = 0;
            cursor_x += packet[1];
            cursor_y -= packet[2];
            if (cursor_x < 0) cursor_x = 0;
            if (cursor_x > 79) cursor_x = 79;
            if (cursor_y < 0) cursor_y = 0;
            if (cursor_y > 24) cursor_y = 24;
            volatile char *vga = (char*)0xB8000;
            int offset = (cursor_y * 80 + cursor_x) * 2;
            vga[offset] = 'X';
            vga[offset+1] = 0x0E;
        }
        status = inb(MOUSE_STATUS);
    }
}
