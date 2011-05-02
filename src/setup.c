#include "multiboot.h"
#include "console.h"
#include "string.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
/* This function will be called by start.S, and some multiboot stuff
will be shoved in its butt */
void setup(struct multiboot_info *mb_info)
{
	
	clear();	//Get rid of old stuff like BIOS messages
	
	// ascii art.  / PopUp
	
	kprint("   _______  _  _________ _  _  _  \n");
	kprint("  / __/ _ \\/ \\|_   _   _|_|\\ \\/ / \n");
	kprint("  | __/  _/ _ \\ | | | | | | >  <  \n");
	kprint("  |_| |__\\_/ \\_\\|_| |_| |_|/_/\\_\\ \n");
	kprint(" ---------------------------------\n");
	kprint("   > the strangest way of life <  \n");
	kprint(" ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	
	// gdt
	
	kprint(" > Initializing GDT...\n");
	gdt_init();
	
	// idt
	
	kprint(" > Initializing IDT...\n");
	idt_init();
	
	// pic
	
	kprint(" > Initializing PIC...\n");
	pic_init();
	
	kprint(" > Infinite awesomeness loading :\n\n");

	/*asm volatile ("int $0x3");
	asm volatile ("int $0x4"); 
	asm volatile ("int $0x8");
	asm volatile ("int $0x10");*/
	
	while(1)	//Endless loop of awesome, make sure it doesn't exit
	{
		
		/*int i,n,s = 0,r = 0;
		
		for (i = 0; i <= 1000000; i++)
			if (s < (i/10000))
				prg_bar(i/10000, 40, CON_DGREY, CON_LGREY), s = i/10000;
			else
				for (n = 0; n <= 200; n++)
					r = r + n % 200;
		
		*/
	}
	
}

/* the raw logo : 

  _______  _  _________ _  _  _
 / __/ _ \/ \|_   _   _|_|\ \/ /
 | __/  _/ _ \ | | | | | | >  <
 |_| |__\_/ \_\|_| |_| |_|/_/\_\
 
 */
