global load_idt
global keyboard_asm_handler

extern keyboard_handler

; =========================
; Load IDT
; =========================
load_idt:
    mov eax, [esp+4]
    lidt [eax]
    ret

; =========================
; Keyboard Interrupt Handler
; =========================
keyboard_asm_handler:
    pusha
    call keyboard_handler

    mov al, 0x20
    out 0x20, al   ; send EOI to PIC

    popa
    iretd