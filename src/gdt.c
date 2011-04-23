//FIXME: This whole thing is so broken.
#include "stdint.h"
#include "mm/gdt.h"

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
static void gdt_addentry(int index, uint32_t base, uint32_t limit, int flags);

void gdt_addentry(int index, uint32_t base, uint32_t limit, int flags)
{
	gdt[index].base_low = (base & 0xffff);		//Lower 16 bits of the base
	gdt[index].base_middle = (base >> 16) & 0xff;	//middle 8 bits of the base
	gdt[index].base_high = (base >> 24) & 0xff;	//higher 8 bits of the base
	gdt[index].limit_low = (limit & 0xffff);	//lower 16 bits of the sector limit
	gdt[index].flags = flags;
}

void gdt_init(void)
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base  = (uint32_t)&gdt;

	gdt_addentry(0, 0, 0, 0);
	gdt_addentry(1, 0, 0xffffffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT | 
		GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
	gdt_addentry(2, 0, 0xffffffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
        GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT);
    gdt_addentry(3, 0, 0xffffffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
        GDT_FLAG_CODESEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
    gdt_addentry(4, 0, 0xffffffff, GDT_FLAG_SEGMENT | GDT_FLAG_32_BIT |
        GDT_FLAG_DATASEG | GDT_FLAG_4K_GRAN | GDT_FLAG_PRESENT | GDT_FLAG_RING3);
    
    gdt_load(gdt_ptr);
}
