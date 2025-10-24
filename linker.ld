OUTPUT_FORMAT("elf64-x86-64")
ENTRY(kernel_start64)

SECTIONS {
  . = 0x100000;
  .text : { *(.text*) }
  .data : { *(.data*) }
  .bss  : { *(.bss*) }
}
