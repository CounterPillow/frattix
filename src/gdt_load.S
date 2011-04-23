.global gdt_load
gdt_load:
	mov 4(%esp), %eax
	lgdt (%eax)
	
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ljmp $0x8, $.1
.1:
	ret 
