// Works now!
#include "console.h"
#include "stdint.h"
#include "gdt.h"

#define GDT_FLAG_DATASEG 0x02	//Contains Data
#define GDT_FLAG_CODESEG 0x0a	//Contains Code
#define GDT_FLAG_TSS     0x09
 
#define GDT_FLAG_SEGMENT 0x10
#define GDT_FLAG_RING0   0x00	//Kernel-Ring
#define GDT_FLAG_RING3   0x60	//User-Ring
#define GDT_FLAG_PRESENT 0x80
 
#define GDT_FLAG_4K_GRAN 0x8
#define GDT_FLAG_32_BIT  0x4

gdt_entry_t gdt[5];
gdt_ptr_t gdt_ptr;

extern void gdt_load(uint32_t);
static void gdt_addentry(int, uint32_t, uint32_t, uint8_t, uint8_t);

// adds an entry to the GDT  / PopUp
void gdt_addentry (int i, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access)
{
	
	gdt[i].base_low    = (base & 0x00FFFF);
	gdt[i].base_middle = (base >> 16) & 0x00FF;
	gdt[i].base_high   = (base >> 24);
	
	gdt[i].limit_low = (limit & 0x0FFFF);
	gdt[i].flags     = (limit >> 16) & 0x0F; 
	
	gdt[i].flags  = gdt[i].flags | (flags << 4);
    gdt[i].access = access;
	
}

// init the GDT  / PopUp
void gdt_init(void)
{
	
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base  = (void *)&gdt;
	
	// PRESENT | SEGMENT | RING0 | CODESEG = 0x9A
	// PRESENT | SEGMENT | RING0 | DATASEG = 0x92
	
	// PRESENT | SEGMENT | RING3 | CODESEG = 0xFA
	// PRESENT | SEGMENT | RING3 | DATASEG = 0xF2
	
	// GDT_FLAG_4K_GRAN | GDT_FLAG_32_BIT = 0xC
	
	gdt_addentry(0, 0, 0, 0, 0);                // Null segment
    gdt_addentry(1, 0, 0xFFFFFFFF, 0xC, 0x9A); // Code segment
    gdt_addentry(2, 0, 0xFFFFFFFF, 0xC, 0x92); // Data segment
    gdt_addentry(3, 0, 0xFFFFFFFF, 0xC, 0xFA); // User mode code segment
    gdt_addentry(4, 0, 0xFFFFFFFF, 0xC, 0xF2); // User mode data segment
	
	// we need TSS later  / PopUp
	
    gdt_load((uint32_t)&gdt_ptr);
	
}
