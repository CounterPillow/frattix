.global idt_load

idt_load:
	mov 4(%esp), %eax	# Move the pointer, given as argument, to %eax
	lidt (%eax)			# Load the idt from the pointer given in %eax
	ret
