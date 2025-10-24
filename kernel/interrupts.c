#include <stdint.h>

struct IDTEntry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  type_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;
} __attribute__((packed));

struct IDTR {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

extern void isr_stub_table();
extern void load_idt(struct IDTR* idtr);

#define IDT_ENTRIES 256
static struct IDTEntry idt[IDT_ENTRIES];

static void set_idt_entry(int n, uint64_t handler) {
    idt[n].offset_low  = handler & 0xFFFF;
    idt[n].selector    = 0x08;
    idt[n].ist         = 0;
    idt[n].type_attr   = 0x8E;
    idt[n].offset_mid  = (handler >> 16) & 0xFFFF;
    idt[n].offset_high = (handler >> 32) & 0xFFFFFFFF;
    idt[n].zero        = 0;
}

void idt_init() {
    uint64_t *stub = (uint64_t*)&isr_stub_table;
    for (int i = 0; i < IDT_ENTRIES; i++)
        set_idt_entry(i, stub[i]);
    struct IDTR idtr;
    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint64_t)&idt;
    load_idt(&idtr);
}

void isr_handler() {
    // temporary handler
}
