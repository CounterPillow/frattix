#include "console.h"
#include "string.h"

static char * const conmem = (char*)0xb8000;	// Where characters get written
static int cur_x = 0, cur_y = 0; // X and Y positions of the pointer
static int sav_x = 0, sav_y = 0; // X/Y variables for cur_save

static char cur_color = CON_BLACK * 0x10 +  CON_LGREY; // colors! / PopUp
static char sav_color = 0; // color_save / PopUp



void set_color  (char fgc, char bgc) { cur_color = bgc * 0x10 + fgc; }
void color_save () { sav_color = cur_color; }
void color_load () { cur_color = sav_color; }

void cur_set  (short x, short y) { cur_x = x; cur_y = y; }
void cur_save () { sav_x = cur_x; sav_y = cur_y; }
void cur_load () { cur_x = sav_x; cur_y = sav_y; }



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

// progressbar. Uses cur_save!  / PopUp
void prg_bar (int pro, unsigned char size, char fgc, char bgc)
{
	
	cur_save();
	color_save();
	int i, perc;
	
	/*if (perc > 0)
		pro = (perc*100)/size;
	else
		pro = 0;*/
		
	perc = size * pro / 100;
	
	
	set_color(fgc, bgc);
	for (i = 0; i < perc; i++)
		kprint(" ");
		
	set_color(bgc, fgc);
	for (; i < size; i++)
		kprint(" ");
	
	
	set_color(fgc, bgc);
	cur_load();
	
	cur_x += (size / 2) - 2;
	
	if ((size / 2) - 2 >= perc) set_color(bgc, fgc);
	kprint(itoa(pro / 100 % 10));
	
	if ((size / 2) - 1 >= perc) set_color(bgc, fgc);
	kprint(itoa(pro / 10 % 10));
	
	if ((size / 2) - 0 >= perc) set_color(bgc, fgc);
	kprint(itoa(pro % 10));
	
	if ((size / 2) + 1 >= perc) set_color(bgc, fgc);
	kprint("%");
	
	
	color_load();
	cur_load();
	
	/*kprint("[");
	kprint(itoa(pro / 100 % 10));
	kprint("]");*/
	
}
