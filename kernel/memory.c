#include <stdint.h>

#define PAGE_SIZE 4096
extern uint64_t kernel_end;

uint64_t next_free_page = (uint64_t)&kernel_end;

void *alloc_page() {
    void *page = (void*)next_free_page;
    next_free_page += PAGE_SIZE;
    return page;
}
