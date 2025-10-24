#include <stdint.h>
#include "../drivers/io.h"

#define KBD_DATA 0x60
#define KBD_STATUS 0x64

static const char keymap[128] = {
  0,27,'1','2','3','4','5','6','7','8','9','0','-','=', '\b',
  '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
  'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z',
  'x','c','v','b','n','m',',','.','/',0,'*',0,' ',0
};

void keyboard_handler() {
    unsigned char status = inb(KBD_STATUS);
    if (status & 1) {
        unsigned char sc = inb(KBD_DATA);
        if (!(sc & 0x80)) {
            char c = keymap[sc];
            if (c) {
                volatile char *vga = (char*)0xB8000;
                vga[0] = c;
                vga[1] = 0x0F;
            }
        }
    }
}
