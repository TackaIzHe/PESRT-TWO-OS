[bits 32]
idt_load:
    pusha
    lidt [eax]
    popa
    ret