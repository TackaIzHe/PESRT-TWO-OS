scank:
    hlt
    mov eax, [keypress]
    test eax, eax
    jz .sleep   ; Если клавиши нет, уходим в сон
    ret

.sleep:
    jmp wait_for_key
