bits 32

global keyboard_asm_handler
extern keyboard_handler

keyboard_asm_handler:

    pusha              ; save registers

    call keyboard_handler
  
    mov al, 0x20       ; send EOI to PIC 
    out 0x20, al

    popa               ; restore registers
    iret
