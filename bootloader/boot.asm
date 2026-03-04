[org 0x7C00]
bits 16

start:
    mov si, message

print:
    lodsb
    cmp al, 0
    je done

    mov ah, 0x0E
    mov bh, 0x00
    mov bl, 0x07
    int 0x10

    jmp print

done:
    jmp $

message db "yoo wassup, im the bootloader :)", 0

times 510 - ($ - $$) db 0
dw 0xAA55