#include <stdint.h>

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

idt_entry idt[256];
idt_ptr idtp;

extern "C" void isr_test();

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_low = handler & 0xFFFF;
    idt[n].selector   = 0x08;
    idt[n].zero       = 0;
    idt[n].type_attr  = 0x8E;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init() {
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    for(int i=0;i<256;i++){
        set_idt_gate(i,(uint32_t)isr_test);
    }

    asm volatile("lidt %0" : : "m"(idtp));
}

extern "C" void kernel_main() {

    idt_init();

    asm volatile("int $0x21");

    while(1);
}