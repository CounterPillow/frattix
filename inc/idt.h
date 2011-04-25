#ifndef IDT_H
#define IDT_H

#include "stdint.h"


struct idt_entry
{
	
	uint16_t base_low;	//lower 16 address bits where we'll jump as soon as the interrupt is recieved
	uint16_t kselect;	//Kernel selector
	uint8_t	 iszero;	//Flag whether it should always be zero
	uint8_t  flags;		//even more flags!
	uint16_t base_high;	//upper 16 bits of the address where we'll jump
	
} __attribute__((packed));

struct idt_ptr
{
	
	uint16_t limit;
	void     *p;
	
} __attribute__((packed));

typedef struct idt_entry idt_entry_t;
typedef struct idt_ptr idt_ptr_t;

void idt_init(void);
void idt_set_entry(int i, uint32_t base, uint16_t k, uint8_t flags);

#endif
