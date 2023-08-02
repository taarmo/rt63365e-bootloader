
MEMORY
{
	RAM1 (rwx) : ORIGIN = 0x80000000, LENGTH = 30M 
	RAM2 (rwx) : ORIGIN = 0x81e00000, LENGTH = 2M 
	FLASH (rx) : ORIGIN = 0xbfc00000, LENGTH = 8M 
}

__stack_size = 0x1200;

ENTRY(__start)

SECTIONS
{
	.init : {
		. = ALIGN(32);
		_inits_sym = .;
		*(.init)
		*(.init.*)
		_inite_sym = .;
		. = ALIGN(32);
	} > FLASH

	.rodata : {
		. = ALIGN(32);
		_rodata_start = .;
 	   	*(.rodata)
 	   	*(.rodata.*)
		_rodata_end = .;
		. = ALIGN(32);
 	 } > RAM2 AT > FLASH		/* read-only data */	

	.text : {
		. = ALIGN(32);
		_stext = .;
		*(.text.init_main)
		*(.text.main)
		*(.text.*)
		_etext = .;
		. = ALIGN(32);
	} > RAM2 AT>FLASH

	.data : { 
		. = ALIGN(32);
		_sdata = .;
		*(.data.*) 
		_gp = ALIGN(32);
		*(.data) 
		_edata = .;
		. = ALIGN(32);
	} > RAM2 AT>FLASH	/* initialized data */

	.bss : { 
		. = ALIGN(32);
		_bss_start = .;
		*(.bss) 
		*(.bss.*) 
		*(.sbss)
		*(.sbss*)
		_bss_end = .;
		. = ALIGN(32);
	} > RAM2	/* cleared-to-zero data */

	.stack : {
		. = ALIGN(32);
		_stack_end = .;
		. = . + __stack_size;
		*(.stack)
		_stack_addr = .;
		. = ALIGN(32);
	} > RAM2


	/*
	 * Debug info
	 */

	/* stabs debug sections */
	.stab 0:		{ *(.stab) } .stabstr 0:		{ *(.stabstr) }

	/* DWARF debug sections */
	.debug 0:		{ *(.debug) }
	.debug_srcinfo 0:	{ *(.debug_srcinfo) }
	.debug_aranges 0:	{ *(.debug_aranges) }
	.debug_pubnames 0:	{ *(.debug_pubnames) }
	.debug_sfnames 0:	{ *(.debug_sfnames) }
	.line 0:		{ *(.line) }
	/*.note.gnu.build-id*/
	/DISCARD/ :
	{
		*(.note*)
		*(.reginfo) 
		*(.MIPS.abiflags)
	}
}

/*_init_size = _inite_sym - _inits_sym;*/
_init_size = SIZEOF(.init);
/*_rodata_size = __rodata_end - __rodata_start;*/
_rodata_size = SIZEOF(.rodata);
/*_text_size = _etext - _stext;*/
_text_size = SIZEOF(.text);
/*_data_size = _edata - _sdata;*/
_data_size = SIZEOF(.data);
/*_data_size = __bass_end - __bss_start */ 
_bss_size = SIZEOF(.bss);

_init_rodata = _init_size;
_init_text_flash = _init_size + _rodata_size;
_fin_text_flash = _init_text_flash + _text_size;
_init_data_flash = _init_size + _rodata_size + _text_size;
_fin_data_flash = _init_data_flash + _data_size;

_size_bootloader_ram = _rodata_size + _text_size + _data_size; 

