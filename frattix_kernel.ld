/*
 *This is the linker script. Linking a kernel needs some special stuff done,
 *which is defined in here.
 */
 
/*Entry point*/
ENTRY(_start)

SECTIONS
{
	/*Load Kernel at 1MB*/
	. = 0x100000;
	/*
	 *Define Sections
	 *First 8kb are used by the multiboot header, the rest of the text
	 *section are for the standard contents
	 */
	.text :
	{
		*(multiboot)	/*Multiboot Header. 8KB*/
		*(.text)		/*Standard .text section.*/
	}
	.data ALIGN(4096) :
	{
		*(.data)
	}
	.rodata ALIGN(4096) :
	{
		*(.rodata)
	}
	.bss ALIGN(4096) : {
		*(.bss)
	}
}
