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

struct registers
{
   uint32_t ds;                  // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} ;

typedef struct idt_entry idt_entry_t;
typedef struct idt_ptr idt_ptr_t;
typedef struct registers registers_t;

void idt_init(void);

#endif
