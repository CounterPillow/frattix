#ifndef DESCRIPTOR_TABLE_H
#define DESCRIPTOR_TABLE_H

#include "stdint.h"
struct gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	int flags;
	uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr_struct
{
	uint16_t limit;               //Upper 16 bits of the selector limits
	uint32_t base;                //Address of the first gdt_entry struct
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;
typedef struct gdt_entry gdt_entry_t;	//I'm lazy.

void gdt_init(void);

#endif
