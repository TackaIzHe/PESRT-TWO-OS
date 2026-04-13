global pic_set_mask
[bits 32]
pic_set_mask:
    pusha
    mov     al, 0xFF
    out     0x21, al          ; mask master

    mov     al, 0xFF
    out     0xA1, al          ; mask slave

    mov     al, 0x11
    out     0x20, al          ; ICW1 master

    mov     al, 0x11
    out     0xA0, al          ; ICW1 slave

    mov     al, 0x20
    out     0x21, al          ; ICW2 master

    mov     al, 0x28
    out     0xA1, al          ; ICW2 slave

    mov     al, 0x04
    out     0x21, al          ; ICW3 master

    mov     al, 0x02
    out     0xA1, al          ; ICW3 slave

    mov     al, 0x01
    out     0x21, al          ; ICW4 master

    mov     al, 0x01
    out     0xA1, al          ; ICW4 slave
    popa
    ret