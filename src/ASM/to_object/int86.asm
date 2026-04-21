; ; pcboot - bootable PC demo/game kernel (NASM port)
; ; Copyright (C) 2018-2019 John Tsiombikas <nuclear@member.fsf.org>
; ; Translated to NASM syntax by ChatGPT
; ;
; ; This program is free software: you can redistribute it and/or modify
; ; it under the terms of the GNU General Public License as published by
; ; the Free Software Foundation, either version 3 of the License, or
; ; (at your option) any later version.

; ; --- Global definitions ---
; global int86

; ; --- Data section ---
; section .data
;     ; Pseudo-descriptor for real-mode IDT (pointing to IVT at 0x0000)
;     rmidt:      dw 0x3FF          ; limit (1023)
;                 dd 0x00000000     ; base (0x0000)

;     ; Saved state for protected mode IDTR
;     saved_idtr: dw 0              ; limit
;                 dd 0              ; base

;     ; Saved registers
;     saved_esp:  dd 0
;     saved_ebp:  dd 0
;     saved_eax:  dd 0
;     saved_es:   dw 0
;     saved_ds:   dw 0
;     saved_flags: dw 0
;     saved_if:   db 0
;     saved_pic1_mask: db 0
;     saved_pic2_mask: db 0

;     ; Placeholder for the "int" instruction we'll patch
;     int_op:     db 0xCD, 0x00       ; int xx (xx will be patched at runtime)

; section .text
;     bits 32

; ; -----------------------------------------------------------------------------
; ; int86 - Call 16-bit BIOS interrupt from protected mode (unreal mode)
; ; Input:  [ebp+12] = pointer to int86regs structure
; ;         [ebp+8]  = interrupt number (e.g., 0x10)
; ; Output: Registers modified as per BIOS call
; ; -----------------------------------------------------------------------------
; int86:
;     push    ebp
;     mov     ebp, esp
;     pusha

;     call    get_intr_flag
;     mov     [saved_if], al
;     cli

;     ; Save current IDTR and load real-mode IDT (IVT)
;     sidt    [saved_idtr]
;     lidt    [rmidt]

;     ; Save PIC masks
;     push    dword 0
;     call    get_pic_mask
;     add     esp, 4
;     mov     [saved_pic1_mask], al

;     push    dword 1
;     call    get_pic_mask
;     add     esp, 4
;     mov     [saved_pic2_mask], al

;     ; Patch the 'int' instruction with the requested interrupt number
;     mov     ebx, int_op
;     mov     al, [ebp+8]           ; interrupt number
;     mov     [ebx+1], al           ; patch the operand

;     ; Long jump to switch to 16-bit code segment (CS=0x30)
;     jmp     far .real_mode_start

; .real_mode_start:
;     bits 16

;     ; Clear protection bit in CR0
;     mov     eax, cr0
;     and     eax, 0xFFFE
;     mov     cr0, eax

;     ; Load CS with 16-bit selector (0)
;     jmp     0x0000:.mode16

; .mode16:
;     ; Zero all segment registers
;     xor     ax, ax
;     mov     ds, ax
;     mov     es, ax
;     mov     ss, ax
;     mov     fs, ax
;     mov     gs, ax

;     ; Load registers from the int86regs structure
;     mov     eax, esp
;     mov     [saved_esp], eax
;     mov     [saved_ebp], ebp
;     mov     esp, [ebp+12]         ; point ESP to regs struct

;     popa
;     popfw

;     pop     es
;     pop     ds

;     ; Use real-mode stack at 0x7BE0 (below boot sector)
;     mov     sp, 0x7BE0
;     mov     ss, 0

;     ; Call the BIOS interrupt (patched above)
;     call    int_op

;     ; Ensure interrupts are disabled after BIOS call
;     cli

;     ; Save clobbered registers
;     mov     [saved_eax], eax
;     mov     [saved_ds], ds
;     mov     [saved_es], es
;     pushfw
;     pop     [saved_flags]

;     ; Re-enable protected mode
;     mov     eax, cr0
;     or      eax, 1
;     mov     cr0, eax

;     ; Long jump back to 32-bit code (CS=0x08)
;     jmp     far .protected_mode_start

; .protected_mode_start:
;     bits 32

;     ; Reload data segments
;     mov     ax, 0x10
;     mov     ds, ax
;     mov     es, ax
;     mov     ss, ax
;     mov     fs, ax
;     mov     gs, ax

;     ; Restore registers to the int86regs structure
;     mov     ebp, [saved_ebp]
;     mov     esp, [ebp+12]
;     add     esp, 38               ; skip 38 bytes (pushal + pushfw + 2 segs)

;     ; Restore DS and ES
;     mov     ax, [saved_ds]
;     push    ax
;     mov     ax, [saved_es]
;     push    ax

;     ; Restore flags (preserve carry flag from BIOS)
;     pushfw
;     pop     ax
;     and     ax, 0xFFFE            ; clear carry
;     or      ax, [saved_flags]     ; restore original flags
;     push    ax
;     popfw

;     ; Restore general-purpose registers
;     pusha

;     ; Restore stack pointer
;     mov     esp, [saved_esp]

;     ; Restore IDTR
;     lidt    [saved_idtr]

;     ; Restore PIC masks
;     movzx   eax, byte [saved_pic1_mask]
;     push    eax
;     push    dword 0
;     call    set_pic_mask
;     add     esp, 8

;     movzx   eax, byte [saved_pic2_mask]
;     push    eax
;     push    dword 1
;     call    set_pic_mask
;     add     esp, 8

;     ; Keyboard voodoo: clear leftover data from port 0x60
;     in      al, 0x60

;     ; Restore interrupt flag
;     movzx   eax, byte [saved_if]
;     push    eax
;     call    set_intr_flag
;     add     esp, 4

;     popa
;     pop     ebp
;     ret

; ; -----------------------------------------------------------------------------
; ; Helper functions (must be defined elsewhere or stubbed)
; ; -----------------------------------------------------------------------------
; ; These are assumed to be defined in the original code.
; ; You must provide implementations for:
; ;   - get_intr_flag
; ;   - get_pic_mask
; ;   - set_pic_mask
; ;   - set_intr_flag
; ;   - init_pic
; ;
; ; For a minimal working example, you can stub them as:
; ;
; get_intr_flag:
;   pushf
;   pop     eax
;   and     eax, 0x200
;   shr     eax, 9
;   ret

; get_pic_mask:
;   mov     dx, 0x21        ; PIC1
;   cmp     eax, 1
;   jne     .pic1
;   mov     dx, 0xA1        ; PIC2
; .pic1:
;   in      al, dx
;   ret

; set_pic_mask:
;   mov     dx, 0x21
;   cmp     ecx, 1
;   jne     .pic1
;   mov     dx, 0xA1
; .pic1:
;   out     dx, al
;   ret

; set_intr_flag:
;   pushf
;   pop     eax
;   and     eax, 0xFFFFFDFF ; clear IF
;   or      eax, ecx        ; set IF if needed
;   push    eax
;   popf
;   ret

; init_pic:
;   ; Initialize PICs if needed
;   ret
; ; -----------------------------------------------------------------------------

; ; --- Boot signature ---
; times 510-($-$$) db 0
; dw 0xAA55
