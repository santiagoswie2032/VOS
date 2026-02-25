extern "C" void interrupt_handler() {
    char* vga = (char*)0xB8000;
    vga[0] = 'I';
    vga[1] = 0x0F;
}extern "C" void load_idt(uint32_t);

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector   = 0x08;   // kernel code segment
    idt[n].zero       = 0;
    idt[n].type_attr  = 0x8E;   // present, ring 0, interrupt gate
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

extern "C" void isr_test();

void idt_init() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base  = (uint32_t)&idt;

    for (int i = 0; i < 256; i++) {
        set_idt_gate(i, (uint32_t)isr_test);
    }

    asm volatile("lidt %0" : : "m"(idt_ptr));
}


