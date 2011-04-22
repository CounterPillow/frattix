//TODO: Fix vertical line overflow (max is at 25 or something)

#include "console.h"

static char * const conmem = (char*)0xb8000;	//Where characters get written
static int ptr_x, ptr_y;	//X and Y positions of the pointer

void kprint(char text[])	//Prints stuff on the screen. duh.
{
	int i;
	for(i = 0;text[i] != '\0'; i++)
	{
		conmem[(ptr_y * 80 + ptr_x) * 2] = text[i];	//multiplied by 2 because of color bytes.
		ptr_advance();
	}
}

void ptr_advance(void)
{
	if(ptr_x == 80)	//Automatic line breaks
	{
		ptr_x = 0;
		ptr_y++;
	}
	else
	{
		ptr_x++;	
	}
}

void clear(void)	//clears the screen, resets text pointers
{
	int i;
	
	for(i = 0; i < 2000; i++)
	{
		conmem[i*2] = 0;
		conmem[i*2 + 1] = 0x07;	//sets the color to light gray/white, whatever you want to call it.
	}
	
	ptr_x = 0;
	ptr_y = 0;
}
