extern "C" void load_idt(uint32_t);

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector   = 0x08;   // kernel code segment
    idt[n].zero       = 0;
    idt[n].type_attr  = 0x8E;   // present, ring 0, interrupt gate
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}
