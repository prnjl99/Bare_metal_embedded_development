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

  .veneers :
  {
     *(.veneer*)
  } > RAM

 .text :
  {
     *(.text*)
     *(.glue_7)
     *(.glue_7t)
     *(.eh_frame)
     KEEP (*(.init))
     KEEP (*(.fini))
      _etext = .;
  } > FLASH

  _sldata = LOADADDR(.data);

  .data :
  {
    _sdata = .;
    *(.data)
    *(.data*)
    _edata = .;
  } >RAM AT> FLASH

  _slrelocate_intr = LOADADDR(.relocate_intr);

  .relocate_intr :
  {
    _srelocate_intr = .;
    *(.ramvtor2)
    *(.ramfunc2)
    KEEP(*(.ramvtor2 .ramfunc2))
    _erelocate_intr = .;
  } >RAM2 AT> FLASH

  _size_relocate_intr = _erelocate_intr - _srelocate_intr;

  .bss (NOLOAD):
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss SORT(.bss.*) COMMON)
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM

  _end_static = _ebss;
  _heap_start = _end_static;
  _heap_size = 0x100;
  _heap_limit = _end_static + _heap_size;
  _min_stack_size = 0x400;

  /* Link time check to ensure RAM is not overflown by stack and heap */
  .stack_heap_overflow_check :
  {
      . = ALIGN(4);
      . = . + _heap_size;
      . = . + _min_stack_size;
      . = ALIGN(4);
  } > RAM

  .rodata : ALIGN(4)
  {
    *(.rodata)
    *(.rodata*)
    KEEP(*(.rodata))
    KEEP(*(.rodata*))
  } >FLASH

  .ARM.extab :
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } >FLASH

  .ARM :
  {
    *(.ARM.exidx*)
  } >FLASH

  .preinit_array :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH

  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH

  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH
}
