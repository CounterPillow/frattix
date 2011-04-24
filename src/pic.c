// pic.c

#include "pic.h"
#include "idt.h"
#include "stdint.h"
#include "io.h"

void pic_init(void)
{
	// Init Master-PIC
	outb(0x20, 0x11); // Der Initialisierungsbefehl
	outb(0x21, 0x20); // Interruptnummer für IRQ 0
	outb(0x21, 0x04); // IRQ 2 (Slave)
	outb(0x21, 0x01); // ICW 4
	 
	// Slave-PIC initialisieren
	outb(0xa0, 0x11); // Initialisierungsbefehl fuer den PIC
	outb(0xa1, 0x28); // Interruptnummer fuer IRQ 8
	outb(0xa1, 0x02); // IRQ 2 = Slave
	outb(0xa1, 0x01); // ICW 4
	 
	// Alle IRQs aktivieren
	outb(0x20, 0x0);
	outb(0xa0, 0x0);
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
