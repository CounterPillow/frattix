// pic.c

#include "pic.h"
#include "idt.h"
#include "stdint.h"

extern void isr32 ();
extern void isr33 ();
extern void isr34 ();
extern void isr35 ();
extern void isr36 ();
extern void isr37 ();
extern void isr38 ();
extern void isr39 ();

extern void isr40 ();
extern void isr41 ();
extern void isr42 ();
extern void isr43 ();
extern void isr44 ();
extern void isr45 ();
extern void isr46 ();
extern void isr47 ();

extern void isr48 ();

void pic_init(void)
{
	
	remap_int(0x20);
	
	idt_set_entry(32, (uint32_t)isr32, 0x08, 0x8E);
	idt_set_entry(33, (uint32_t)isr33, 0x08, 0x8E);
	idt_set_entry(34, (uint32_t)isr34, 0x08, 0x8E);
	idt_set_entry(35, (uint32_t)isr35, 0x08, 0x8E);
	idt_set_entry(36, (uint32_t)isr36, 0x08, 0x8E);
	idt_set_entry(37, (uint32_t)isr37, 0x08, 0x8E);
	idt_set_entry(38, (uint32_t)isr38, 0x08, 0x8E);
	idt_set_entry(39, (uint32_t)isr39, 0x08, 0x8E);
	
	idt_set_entry(40, (uint32_t)isr40, 0x08, 0x8E);
	idt_set_entry(41, (uint32_t)isr41, 0x08, 0x8E);
	idt_set_entry(42, (uint32_t)isr42, 0x08, 0x8E);
	idt_set_entry(43, (uint32_t)isr43, 0x08, 0x8E);
	idt_set_entry(44, (uint32_t)isr44, 0x08, 0x8E);
	idt_set_entry(45, (uint32_t)isr45, 0x08, 0x8E);
	idt_set_entry(46, (uint32_t)isr46, 0x08, 0x8E);
	idt_set_entry(47, (uint32_t)isr47, 0x08, 0x8E);
	
	idt_set_entry(48, (uint32_t)isr48, 0x08, 0x8E);
	
}

void remap_int(int num)
{
	
	outb(PIC_MCOMMAND, 0x11);
	outb(PIC_MCOMMAND, 0x11);
	
	outb(PIC_MDATA, num);
    outb(PIC_SDATA, num + 8);
	
	outb(PIC_MDATA, 0x04);
    outb(PIC_SDATA, 2);
	
	outb(PIC_MDATA, 0x01);
	outb(PIC_SDATA, 0x01);
	
	/*outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);*/
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
	
}

void pic_mask_irqs(uint16_t mask)
{
	
    outb(PIC_MIMR, (uint8_t) mask);
    outb(PIC_SIMR, (uint8_t) mask >> 8);
   
}

void pic_send_eoi(int irq)
{
	
    outb(PIC_MCOMMAND, 0x20);
    if (irq > 7) outb(PIC_SCOMMAND, 0x20);
	
}


void outb(uint16_t port, uint8_t data)
{
	
    asm volatile( "outb %0, %1" : : "a"(data), "Nd"(port) );
	
}