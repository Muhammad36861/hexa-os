#include "../drivers/io.h"
#include <stdint.h>

#define PIT_CMD 0x43
#define PIT_DATA 0x40

void timer_init(uint32_t freq) {
    uint32_t divisor = 1193180 / freq;
    outb(PIT_CMD, 0x36);
    outb(PIT_DATA, divisor & 0xFF);
    outb(PIT_DATA, divisor >> 8);
}
