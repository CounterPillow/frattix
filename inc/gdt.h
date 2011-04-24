#ifndef DESCRIPTOR_TABLE_H
#define DESCRIPTOR_TABLE_H

#include "stdint.h"

struct gdt_entry // 64 bytes
{
	
	uint16_t limit_low;  // 1-2
	uint16_t base_low;   // 3-4
	uint8_t base_middle; // 5
	uint8_t access;      // 6
	uint8_t flags;       // 7 (and limit)
	uint8_t base_high;   // 8
	
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
