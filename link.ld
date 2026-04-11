ENTRY(_start)

/* ---------- физические адреса (без paging) ---------------- */
PHDRS
{
  boot    PT_LOAD FLAGS(5);  /* 0x7C00  R+E  */
  kernel  PT_LOAD FLAGS(5);  /* 0x8000  R+E  */
  data    PT_LOAD FLAGS(6);  /* R+W        */
}

SECTIONS
{
  /* ---------- MBR-bootstub (512 байт) --------------------- */
  . = 0x7C00;
  .boot : ALIGN(512)
  {
    *(.boot)
    . = 0x7DFE;        /* signature 0x55AA */
    SHORT(0x55AA);
  } :boot

  /* ---------- ядро ---------------------------------------- */
  . = 0x8000;
  .text : ALIGN(4)
  {
    *(.text .text.*)
  } :kernel

  .rodata : ALIGN(4)
  {
    *(.rodata .rodata.*)
  } :kernel

  .data : ALIGN(4)
  {
    *(.data .data.*)
  } :data

  /* ---------- BSS (обнуляется runtime) -------------------- */
  .bss (NOLOAD) : ALIGN(4)
  {
    _bss_start = .;
    *(.bss .bss.*)
    *(COMMON)
    _bss_end = .;
  }

  /* ---------- стек 8 Кбайт -------------------------------- */
  .stack (NOLOAD) : ALIGN(16)
  {
    _stack_bottom = .;
    . += 0x2000;
    _stack_top = .;
  }

  /* ---------- IDT 256 байт (32 gate * 8) ------------------ */
  .idt (NOLOAD) : ALIGN(8)
  {
    _idt_start = .;
    . += 256;
    _idt_end = .;
  }

  /* ---------- GDT 24 байта (3 entries) ------------------- */
  .gdt (NOLOAD) : ALIGN(8)
  {
    _gdt_start = .;
    . += 24;
    _gdt_end = .;
  }

  /DISCARD/ : { *(.note*) *(.comment*) *(.eh_frame*) }

  /* ---------- символы для скрипта ------------------------- */
  _kernel_start = 0x8000;
  _kernel_size  = SIZEOF(.text) + SIZEOF(.rodata) + SIZEOF(.data);
  _kernel_end   = .;
}
