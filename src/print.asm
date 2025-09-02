main:
    call print 
       
    jmp $

print:
    mov si, mess
    mov ah,0x0E
    .r:
    lodsb
    cmp al,'\0'
    jne .l
    jmp .exit
    .l:
    int 0x10
    jmp .r
    .exit:
    ret





%define ENDL 0x0D, 0x0A
mess db "yeee second Boot",ENDL,'\0'