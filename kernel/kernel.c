void kernel_main(void) {
    char *video = (char*)0xb8000;
    const char *msg = "Hexa OS Kernel Initialized";
    int i = 0;
    while (msg[i]) {
        video[i * 2] = msg[i];
        video[i * 2 + 1] = 0x0F;   // white on black
        i++;
    }
    for(;;);  // halt
}
