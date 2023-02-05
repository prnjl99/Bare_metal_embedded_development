ENTRY(_resetHandler);

MEMORY
{
  flash(rx)  : ORIGIN = 0x08000000, LENGTH = 1024k
  sram1(rwx) : ORIGIN = 0x20000000, LENGTH = 96k  /* SRAM1 */
}

_initialStackPoniter = ORIGIN(sram1) + LENGTH(sram1);    /* stack starts from the end of SRAM */

SECTIONS {
  .vectors  : { KEEP(*(.vtors)) } > flash
  .text     : { *(.text*) }       > flash
  .rodata   : { *(.rodata*) }     > flash

  .data : {
    _startdata = .;   /* start of.data section */
    *(.first_data)
    *(.data SORT(.data.*))
    _enddata = .;  /* end of .data section */
  } > sram1 AT > flash
  _absaddrdata = LOADADDR(.data);

  .bss : {
    _startbss = .;              /* start of .bss section */
    *(.bss SORT(.bss.*) COMMON)
    _endbss = .;              /* end of .bss section */
  } > sram1

  . = ALIGN(8);
  _end = .;
}
