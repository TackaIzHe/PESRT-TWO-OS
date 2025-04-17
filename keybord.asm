section .data
idt_pointer dw idt_end - idt - 1      ; Размер IDT
    	    dw idt  
idt resb 256 * 8                      ; Резервируем место для IDT (256 векторов)


section .text
[bits 32]

global keyboard_interrupt_handler
global keybord_init

; Обработчик прерывания клавиатуры



keybord_init:
	push es
	push ds                                 ; Отключаем прерывания
    lidt [idt_pointer]                 ; Загружаем адрес IDT

    ; Устанавливаем обработчик прерывания клавиатуры
    ; Вектор 0x21 (IRQ1)
    ; Здесь мы просто указываем адрес обработчика
    ; Предполагается, что обработчик находится после IDT
    mov dword [idt + 0x21 * 8], keyboard_interrupt_handler ; Устанавливаем адрес обработчика
    mov dword [idt + 0x21 * 8 + 4], 0x08 ; Сегмент кода (например, 0x08)
	sti
	.l:
    hlt                                 ; Ожидание прерывания
    jmp .l
	pop ds
	pop es
	ret

keyboard_interrupt_handler:
	pusha
	in al, 0x60                         ; Читаем код сканирования из порта 0x60
    ; Здесь можно обработать код сканирования
    ; Например, выводить его на экран или сохранять в буфер

    out 0x20, al                        ; Посылаем сигнал об окончании обработки прерывания
	popa
	iret
idt_end: