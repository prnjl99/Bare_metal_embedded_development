ENTRY(reset_handler)

MEMORY
{
  /* LENGTH = 0x00008000 */
  RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 32K
  /* LENGTH = 0x00040000 */
  FLASH (rx)      : ORIGIN = 0x00000000, LENGTH = 256K
}

SECTIONS
{
  .isr_vector  : { KEEP(*(.isr_vector)) } > FLASH

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
