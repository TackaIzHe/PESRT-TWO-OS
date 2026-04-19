global _start
global call_interrupt
global enter_protected_mode
_start:
section .text
    [bits 32]
    [extern start_kernel]
    call start_kernel
    jmp $

call_interrupt:
    push bp
    mov bp, sp

    ; Сохраняем регистры, которые будем использовать
    push ax
    push bx
    push cx
    push dx
    push di
    push es

    ; Извлекаем параметры из стека:
    ; [bp+8] : AX (включая AH и AL)
    ; [bp+6] : BX
    ; [bp+4] : DI
    ; [bp+2] : ES

    mov ax, [bp+8]   ; ← ЗАГРУЖАЕМ ПЕРЕДАННЫЙ AX (0x4F00, 0x4F01, 0x4F02)
    mov bx, [bp+6]   ; ← CX в BX, потому что в VBE 0x4F01 используется CX
    mov di, [bp+4]
    mov es, [bp+2]

    ; 💡 ВАЖНО: VBE функции 0x4F01 используют CX, но мы передали его в BX!
    ; Поэтому нужно скопировать BX → CX
    mov cx, bx       ; ← КОПИРУЕМ BX В CX, потому что VBE 0x4F01 ожидает CX

    ; Теперь всё готово: AX=0x4F00/0x4F01/0x4F02, CX=режим, ES:DI=буфер
    int 0x10

    ; Восстанавливаем регистры
    pop es
    pop di
    pop dx
    pop cx
    pop bx
    pop ax

    mov sp, bp
    pop bp
    ret

enter_protected_mode:
    cli                         ; Запретить прерывания

    ; Загрузить GDTR с адресом GDT
    lgdt [GDT_descriptor]              ; gdt_ptr — глобальная переменная из C

    ; Включить бит PE (Protection Enable) в CR0
    mov eax, cr0
    or eax, 1                   ; Установить бит 0 (PE)
    mov cr0, eax
    [extern exit_real_mode]
    ; Дальнейший переход (far jump) — переключает CS на сегмент кода в Protected Mode
    ; Это необходимо для очистки конвейера и загрузки нового CS
    jmp 0x08:exit_real_mode   ; 0x08 — селектор кодового сегмента (GDT[1])

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

CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start
