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
 
#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT  0x400

gdt_entry_t gdt[5];
gdt_ptr_t gdt_ptr;

extern void gdt_load(gdt_ptr_t ptr);
static void gdt_addentry(int index, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access);

void gdt_addentry(int i, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access)
{
	
	gdt[i].base_low    = (base & 0xFFFF);
    gdt[i].base_middle = (base >> 16) & 0xFF;
    gdt[i].base_high   = (base >> 24) & 0xFF; 
    
    gdt[i].limit_low   = (limit & 0xFFFF);
    gdt[i].flags       = (limit >> 16) & 0x0F; 
    
    gdt[i].flags      |= flags & 0xF0;
    gdt[i].access      = access;
	
}

void gdt_init(void)
{
	
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base  = (uint32_t)&gdt; // a double pointer might be wrong
    
	gdt_addentry(0, 0, 0, 0, 0);                // Null segment
    gdt_addentry(1, 0, 0xFFFFFFFF, 0xCF, 0x9A); // Code segment
    gdt_addentry(2, 0, 0xFFFFFFFF, 0xCF, 0x92); // Data segment
    gdt_addentry(3, 0, 0xFFFFFFFF, 0xCF, 0xFA); // User mode code segment
    gdt_addentry(4, 0, 0xFFFFFFFF, 0xCF, 0xF2); // User mode data segment
	
    gdt_load(gdt_ptr);
	
	//kprint("test!\n");
	
}
