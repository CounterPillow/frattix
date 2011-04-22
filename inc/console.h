#ifndef CONSOLE_H
#define CONSOLE_H
/*2 bytes for each char, 1 for the character, 1 for the color code
 *80 characters per line
 *25 lines?
 */
 
void kprint(char text[]);
void ptr_advance(void);
void clear(void);
#endif
