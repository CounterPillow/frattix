#ifndef CONSOLE_H
#define CONSOLE_H
/*2 bytes for each char, 1 for the character, 1 for the color code
 *80 characters per line
 *25 lines?
 */

// colors

#define CON_BLINK   0b1000

#define CON_BLACK   0x0
#define CON_BLUE    0x1
#define CON_GREEN   0x2
#define CON_CYAN    0x3
#define CON_RED     0x4
#define CON_MAGENTA 0x5
#define CON_BROWN   0x6
#define CON_LGREY   0x7

#define CON_DGREY    0x8
#define CON_LBLUE    0x9
#define CON_LGREEN   0xA
#define CON_LCYAN    0xB
#define CON_LRED     0xC
#define CON_LMAGENTA 0xD
#define CON_YELLOW   0xE
#define CON_WHITE    0xF



// functions

void kprint (char text[]);
void cur_advance (char newline);
void scroll (int times);
void clear (void);
void set_color (char fgc, char bgc);

#endif
