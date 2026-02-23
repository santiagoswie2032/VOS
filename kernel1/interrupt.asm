global isr_test

isr_test:
    pusha
    call interrupt_handler
    popa
    iret
