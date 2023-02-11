ENTRY(reset_handler)

_estack = 0x20018000;

MEMORY
{
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 96K
  RAM2 (xrw)      : ORIGIN = 0x10000000, LENGTH = 32K
  FLASH (rx)      : ORIGIN = 0x8000000, LENGTH = 1024K
}

SECTIONS
{
  .isr_vector  : { KEEP(*(.isr_vector)) } > FLASH
  .text :
  {
     *(.text*)
      _etext = .;
  } > FLASH

  .data : 
  {
    _sdata = .;
    *(.data)
    *(.data*)
    _edata = .;
  } >RAM AT> FLASH

  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM
}
