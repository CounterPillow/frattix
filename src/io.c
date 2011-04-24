#include "stdint.h"
inline void outb(uint16_t port, uint8_t data)
{
    asm volatile ("outb %0, %1" : : "a" (data), "Nd" (port));
}
inline char inb(uint16_t port)
{
	char result;
	asm volatile ("inb %1, %0" : "=a" (result) : "Nd" (port));
	return result;
}
