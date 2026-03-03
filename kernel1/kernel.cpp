//helper func to wrote to a hardware port ->

void outb(unsigned short port, unsigned char val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

// helper fucn to read from a hardware port

unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

extern "C" void kmain() {
    //initializing GDT and IDT here, also creating a cursor variable to track where i print.
    int cursor = 0;
    unsigned short* vga = (unsigned short*) 0xB8000;

    const char* msg = "Kernel: IDT/GDT Initialization Pending...";
    for(int i = 0; msg[i] != '\0'; i++) {
        vga[cursor++] = (unsigned short) msg[i] | (0x0F << 8);
    }
}extern "C" void interrupt_handler() {
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
extern "C" void idt_init();

extern "C" void kernel_main() {
    idt_init();
    asm volatile("int $0x21");
    while (1);
}


