#ifndef IO_H
#define IO_H
#include "stdint.h"
void outb(uint16_t port, uint8_t data);
char inb(uint16_t port);
#endif
