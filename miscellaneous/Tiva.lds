ENTRY(_Reset)

MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

_stack_start = ORIGIN(SRAM)+LENGTH(SRAM);

SECTIONS {
	.text : {
		KEEP(*(.vector_interrupt));

		. = 0x0000026c;
        * (.text);
		* (.rodata);
		_flash_sdata = .;
    } > FLASH

	. = ORIGIN(SRAM);
	_ram_sdata = .;
    .data : AT (_flash_sdata) {
      	* (.data);
    } > SRAM
    _ram_edata = .;
    _data_size = _ram_edata - _ram_sdata;

	_sbss = .;
    .bss : {
        * (.bss);
    } > SRAM
	_ebss = .;
	_bss_size = _ebss - _sbss;
}
