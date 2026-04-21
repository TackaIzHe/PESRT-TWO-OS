[org 0x7c00]                        
KERNEL_LOCATION equ 0x2000
global low_mem_buffer

; mov ax, 4F02h
; mov bx, 411Ch
; int 0x10

; Читаем структуру vbe_mode_info_t
mov ax, 0
mov es, ax
mov ax, 0x1000
mov di, ax
mov ax, 4F00h
mov bx, 411ch
int 0x10

; Читае структуру vbe_info_t
mov ax, 0
mov es, ax
mov ax, 0x1500
mov di, ax
mov ax, 4F01h
mov bx, 411ch
int 0x10

; mov ah, 0x0E
; mov al, "A"
; int 0x10
mov [BOOT_DISK], dl                 


xor ax, ax                          
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOCATION
mov dh, 2

mov ah, 0x02
mov al, 0x30
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [BOOT_DISK]
int 0x13                ; no error management

mov ah, 0x02  ; Установить позицию курсора
mov bh, 0x00  ; Страница (обычно 0)
mov dh, 0x00  ; Строка
mov dl, 0x00  ; Столбец
int 0x10               ; text mode

mov ah, 0x1
mov ch, 0x5f
int 10h

CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

jmp $
                                    
BOOT_DISK: db 0

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start


[bits 32]
start_protected_mode:
    mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x90000		; 32 bit stack base pointer
	mov esp, ebp
    jmp KERNEL_LOCATION
 
times 510-($-$$) db 0              
dw 0xaa55

low_mem_buffer: