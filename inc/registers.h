#ifndef REGISTERS_H
#define REGISTERS_H
struct register_struct
{
	uint32_t ds;	//Data Segment Selector
	
	//Pushed manually
	uint32_t edi;
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	
	//Interrupt number and, if existent, error code
	uint32_t int_no;
	uint32_t err_code;
	
	// Pushed by the processor automatically.
	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t useresp;
	uint32_t ss; 
};
typedef struct register_struct register_t;
#endif
