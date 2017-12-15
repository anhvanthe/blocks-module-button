ENTRY(Reset_Handler)
_estack = 0x20018000;
_Min_Heap_Size = 0x400;
_Min_Stack_Size = 0x200;
MEMORY
{
  BOOTLOADER (rx) : ORIGIN = 0x08000000, LENGTH = 20K
  FIRMWARE (rx) : ORIGIN = 0x08005000, LENGTH = 200K
  PARAM (rw) : ORIGIN = 0x20000000, LENGTH = 32
  RAM (xrw) : ORIGIN = 0x20000020, LENGTH = 96K - 32
}
INCLUDE firmware.ld.in
SECTIONS
{
  .isr_vector :
  {
    . = ALIGN(8);
    _isr_vector_start = .;
    KEEP(*(.isr_vector))
    . = ALIGN(8);
    _isr_vector_end = .;
  } >ROM
  .module_info :
  {
    . = ALIGN(4);
    _module_info_start = .;
    LONG(0xDA7ADA7A);
    . += 12;
    _module_info_end = .;
    _vendor_info_start = .;
    KEEP(*(.vendor_info))
    _vendor_info_end = .;
  } > ROM
  .text :
  {
    . = ALIGN(8);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(8);
    _etext = .;
  } >ROM
  .rodata :
  {
    . = ALIGN(8);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(8);
  } >ROM
  .ARM.extab :
  {
  . = ALIGN(8);
  *(.ARM.extab* .gnu.linkonce.armextab.*)
  . = ALIGN(8);
  } >ROM
  .ARM : {
 . = ALIGN(8);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
 . = ALIGN(8);
  } >ROM
  .preinit_array :
  {
 . = ALIGN(8);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
 . = ALIGN(8);
  } >ROM
  .init_array :
  {
 . = ALIGN(8);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
 . = ALIGN(8);
  } >ROM
  .fini_array :
  {
 . = ALIGN(8);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
 . = ALIGN(8);
  } >ROM
  ._bl_params ORIGIN(PARAM) : {
    _bl_params = .;
  } >PARAM
  _sidata = LOADADDR(.data);
  .data :
  {
    . = ALIGN(8);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(8);
    _edata = .;
    LONG(0xBA171B4E);
  } >RAM AT> ROM
  . = ALIGN(4);
  .bss :
  {
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } >RAM
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    heap_low = .;
    . = . + _Min_Heap_Size;
    heap_top = .;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }
  .ARM.attributes 0 : { *(.ARM.attributes) }
}
