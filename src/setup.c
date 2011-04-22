#include "multiboot.h"
#include "console.h"
/* This function will be called by start.S, and some multiboot stuff
will be shoved in its butt */
void setup(struct multiboot_info *mb_info)
{
	clear();	//Get rid of old stuff like BIOS messages
	kprint("Hello World!");
	while(1)	//Endless loop of awesome, make sure it doesn't exit
	{
	}
}
