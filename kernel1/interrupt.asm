bits 32

global isr_test
extern interrupt_handler

isr_test:
    pusha                 ; Save all general purpose registers

    call interrupt_handler

    popa                  ; Restore registers
    iret                  ; Return from interrupt