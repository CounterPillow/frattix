#include "console.h"
#include "string.h"

static char * const conmem = (char*)0xb8000;	// Where characters get written
static int cur_x = 0, cur_y = 0; // X and Y positions of the pointer

static char cur_color = CON_BLACK * 0x10 +  CON_LGREY; // colors! / PopUp

// the basic kprint. Simple \r,\n and \b support.  / PopUp
void kprint (char *text)
{
	
	int i;
	
	for(i = 0; text[i] != '\0'; i++)
	{
		
		if (text[i] == '\n')
			cur_advance(1);
		else if (text[i] == '\r')
			cur_x = 0;
		else if (text[i] == '\b')
			cur_x--;
		else if (text[i] == '\t')
		{
			
			int t = 0;
			
			while (t < cur_x) t = t + 8;
			
			cur_x = t - 1;
			cur_advance(0);
			
		}
		else
		{
			
			conmem[(cur_y * 80 + cur_x) * 2] = text[i];	//multiplied by 2 because of color bytes.
			conmem[(cur_y * 80 + cur_x) * 2 + 1] = cur_color; // colorbyte
			cur_advance(0);
			
		}
		
	}
	
}

void cur_advance (char newline) // advance our cursor
{
	
	cur_x++;
	
	if (cur_x > 79 || newline > 0)
	{
		
		cur_x = 0;
		
		if (cur_y >= 24)
			scroll(1);
			
		cur_y++;
		
	}
	
}

// simple scroll routine.  / PopUp
void scroll (int times)
{
	
	int i; // ints might be faster... / PopUp
	
	for (i = 0; i < (25-times) * 160 / sizeof(int); i++)
	{
		
		((int *)conmem)[i] = ((int *)conmem)[i+(160*times/sizeof(int))];
		
	}
	
	for (i = 0; i < 160 * times; i = i + 2)
	{
		
		conmem[(25-times)*160+i] = 0;
		conmem[(25-times)*160+i+1] = cur_color;
		
	}
	
	cur_y = cur_y - times;
	
}

void clear(void)	//clears the screen, resets text pointers
{
	int i;
	
	for(i = 0; i < 2000; i++)
	{
		conmem[i*2] = 0;
		conmem[i*2 + 1] = cur_color;
	}
	
	cur_x = 0;
	cur_y = 0;
}

// sets colors  / PopUp
void set_color (char fgc, char bgc)
{
	
	cur_color = bgc * 0x10 + fgc;
	
}
