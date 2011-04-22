//Assembler File which contains basically the entry point and the multiboot header

#define MB_MN 0x1badb002 //Magic Number for Multiboot Header
#define MB_FLAGS 0x0	//No Flags
#define MB_CHECKSUM -(MB_MN + MB_FLAGS) //Multiboot Checksum

.section multiboot
	//Multiboot-Header
	.align 4
	.int MB_MN
	.int MB_FLAGS
	.int MB_CHECKSUM
.section .text
	.extern setup	//setup is a C-Function which will be called
	
	//Entry point
	.global _start
	
	_start:
		mov $kernel_stack, %esp //Oh hello stack.
		
		//Call our cool setup function
		push %ebx
		call setup
//8kb of stack for our kernel
.section .bss
	.space 8192
	kernel_stack:
