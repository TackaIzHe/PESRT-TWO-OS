section .text
    [bits 32]
    [extern main]
    call main
    jmp $

; global getTackt 

; getTackt:
;     push ds
;     push es
    
;     rdtsc

;     pop es
;     pop ds
;     ret
