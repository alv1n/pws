/******************************************************************************
*	kernel.ld
*	by Alex Chadwick
*   Modified by Ket Bottelier en Alvin Reumer
*
*	A linker script for generation of raspberry pi kernel images, with C
*	code.
******************************************************************************/

SECTIONS {
	/*
	* First and formost we need the .init section, containing the code to 
        * be run first. We allow room for the ATAGs and stack and conform to 
        * the bootloader's expectation by putting this code at 0x8000.
	*/
	.init 0x8000 : {
		*(.init)
	}
	
	/* 
	* Next we put the data. NEW: added .bss section to data
	*/
	.data : {
		*(.data)
		*.c.o(*)
		*(.bss)
	}
	
	/* 
	* Next we put the rest of the code.
	*/
	.text : {
		*.c.o(.text)
		*(.text)
	}
    /*
    * Read-Only data.
    */
    _etext = .;
    .rodata : {
            *(.rodata*)
        }

    COMMON : {
        *(COMMON*)
        }
	/*
	* Finally comes everything else. A fun trick here is to put all other 
	* sections into this section, which will be discarded by default.
	*/
	/DISCARD/ : {
		*(*)
	}
}
