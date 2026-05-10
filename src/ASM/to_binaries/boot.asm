[org 0x7c00]  
KERNEL_LOCATION equ 0x2000
mov [BOOT_DISK], dl                 

xor ax, ax                          
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOCATION
mov dh, 2

; Обнаружелось ограничение QEMU на чтение секторов диска == 0x2E
; Читает от 2 до 46 включительно
mov ah, 0x02
mov al, 46
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [BOOT_DISK]
int 0x13

mov ah, 0x1
mov ch, 0x5f
int 10h

; Получение даных vbe vbe_mode_info_t
mov ax, 0x1000
mov di, ax
mov ax, 0
mov es, ax
mov ax, 0x4F01      
mov cx, 0x11A       
int 0x10

; Получение даных vbe vbe_info_t
mov ax, 0x1100
mov di, ax
mov ax, 0
mov es, ax
mov ax, 0x4F00      
mov cx, 0x11A       
int 0x10

mov ax, 0x4F02
mov cx, 0x411A
mov bx, 0x411A
int 0x10

mov al, 'A'
mov ah, 0x0E
int 0x10

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

; --- Таблица разделов (64 байта) ---
; Первая запись: активный раздел FAT32 (LBA), начиная с 2048, весь диск

times 446-($-$$) db 0            

partition1:
    db 0x80               ; активный
    db 0x00, 0x01, 0x00   ; CHS (не используется, но должен быть валиден)
    db 0x0C               ; тип: FAT32 (LBA)
    db 0xFF, 0xFF, 0xFF   ; CHS конец
    dd 2048               ; LBA начала — **важно!**
    dd 2048*32   ;1мегобайт  ; количество секторов

; Остальные три записи — пустые
partition2: times 16 db 0
partition3: times 16 db 0
partition4: times 16 db 0

dw 0xaa55

; --- Дополнительные данные (если нужно) ---
; times 512*2048 - ($-$$) db 0  ; если нужно "заполнить" до сектора 2048 (опционально)

; times 512 db 0  ; паддинг до 1MB, если вы пишете на флешку

