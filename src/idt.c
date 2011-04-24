#include "idt.h"
#include "stdint.h"
#include "console.h"
#include "string.h"
#include "registers.h"

static idt_entry_t idt[256];
static idt_ptr_t idt_pointer;

extern void idt_load(uint32_t);	//ASM function to load the idt, requires a pointer as argument

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10 ();
extern void isr11 ();
extern void isr12 ();
extern void isr13 ();
extern void isr14 ();
extern void isr15 ();
extern void isr16 ();
extern void isr17 ();
extern void isr18 ();
extern void isr19 ();
extern void isr20 ();
extern void isr21 ();
extern void isr22 ();
extern void isr23 ();
extern void isr24 ();
extern void isr25 ();
extern void isr26 ();
extern void isr27 ();
extern void isr28 ();
extern void isr29 ();
extern void isr30 ();
extern void isr31 ();



static void idt_set_entry(int i, uint32_t base, uint16_t k, uint8_t flags)
{
	
	idt[i].base_low  = (base & 0x0000FFFF);
	idt[i].base_high = (base >> 16) & 0x0000FFFF;
	
	idt[i].kselect = k;
	idt[i].flags   = flags;
	idt[i].iszero  = 0;
	
}

void idt_init(void)
{
	
	idt_pointer.limit = sizeof(struct idt_entry) * 32 - 1;
	idt_pointer.p     = (void *)&idt;
	
	idt_set_entry( 0, (uint32_t)isr0, 0x08, 0x8E);
	idt_set_entry( 1, (uint32_t)isr1, 0x08, 0x8E);
	idt_set_entry( 2, (uint32_t)isr2, 0x08, 0x8E);
	idt_set_entry( 3, (uint32_t)isr3, 0x08, 0x8E);
	idt_set_entry( 4, (uint32_t)isr4, 0x08, 0x8E);
	idt_set_entry( 5, (uint32_t)isr5, 0x08, 0x8E);
	idt_set_entry( 6, (uint32_t)isr6, 0x08, 0x8E);
	idt_set_entry( 7, (uint32_t)isr7, 0x08, 0x8E);
	
	idt_set_entry( 8, (uint32_t)isr8, 0x08, 0x8E);
	idt_set_entry( 9, (uint32_t)isr9, 0x08, 0x8E);
	idt_set_entry(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_entry(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_entry(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_entry(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_entry(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_entry(15, (uint32_t)isr15, 0x08, 0x8E);
	
	idt_set_entry(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_entry(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_entry(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_entry(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_entry(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_entry(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_entry(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_entry(23, (uint32_t)isr23, 0x08, 0x8E);
	
	idt_set_entry(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_entry(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_entry(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_entry(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_entry(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_entry(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_entry(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_entry(31, (uint32_t)isr31, 0x08, 0x8E);
	
	idt_load((uint32_t)&idt_pointer);
	
}

void isr_handler(register_t regs)
{
	if(regs.int_no <= 0x1f)	//Exception!
	{
		kprint("RECIEVED EXCEPTION ");
		kprint(itoa(regs.int_no));
		kprint("\n");
		asm volatile("cli; hlt");
	}else{
		kprint("Interrupt ");
		kprint(itoa(regs.int_no));
		kprint(" recieved.\n");
	}
} 
