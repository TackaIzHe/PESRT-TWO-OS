global _start

_start:
section .text
    [bits 32]
    [extern start_kernel]
    call start_kernel
    jmp $
