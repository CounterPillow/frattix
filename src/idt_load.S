
# IDT_LOAD

.global idt_load
idt_load:
	mov 4(%esp), %eax	# Move the pointer, given as argument, to %eax
	lidt (%eax)			# Load the idt from the pointer given in %eax
	ret



# IDT MACROS

.macro ISR_NOERR y  # define a macro, taking one parameter
  .global isr\y     # \y accesses the first parameter.
  isr\y:
    cli
    push $0
    push \y
    jmp isr_common_stub
.endm

.macro ISR_ERR y
  .global isr\y
  isr\y:
    cli
    push \y
    jmp isr_common_stub
.endm



# IDT COMMON STUB
.extern isr_handler

isr_common_stub:
   pusha                    # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov %ds, %ax              # Lower 16-bits of eax = ds.
   push %eax                 # save the data segment descriptor

   movw $16, %ax  # load the kernel data segment descriptor
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs

   call isr_handler

   pop %eax        # reload the original data segment descriptor
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs

   popa             # Pops edi,esi,ebp...
   add $8, %esp     # Cleans up the pushed error code and pushed ISR number
   sti
   iret           # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP



# IDT FUNCS

ISR_NOERR  0
ISR_NOERR  1
ISR_NOERR  2
ISR_NOERR  3
ISR_NOERR  4
ISR_NOERR  5
ISR_NOERR  6
ISR_NOERR  7

ISR_ERR  8
ISR_NOERR  9
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NOERR 15

ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23

ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31
