#include "multiboot.h"
#include "console.h"
#include "string.h"
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
	
	
	
	//set_color (CON_BLUE, CON_WHITE);
	
	/*kprint("  //       CHICKEN  \n");
	kprint(" <*)___,  SOLUTIONS \n");
	kprint("  \\_  /             \n");
	kprint("    ||     BA-GOK!  \n"); */
	
	kprint(" > Endless loop of awesomeness...");
	
	while(1)	//Endless loop of awesome, make sure it doesn't exit
	{
	}
	
}

/* the raw logo : 

  _______  _  _________ _  _  _
 / __/ _ \/ \|_   _   _|_|\ \/ /
 | __/  _/ _ \ | | | | | | >  <
 |_| |__\_/ \_\|_| |_| |_|/_/\_\
 
 */
