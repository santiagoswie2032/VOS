#include <stdint.h>
#include "../idt.hpp"

// keyboard interrupt from assembly
extern "C" void keyboard_asm_handler();


// Write byte to port
void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}


// IDT structures
idt_entry idt[256];
idt_ptr idtp;


// Set IDT entry
void set_idt_gate(int n, uint32_t handler)
{
    idt[n].base_low  = handler & 0xFFFF;
    idt[n].sel       = 0x08;
    idt[n].always0   = 0;
    idt[n].flags     = 0x8E;
    idt[n].base_high = (handler >> 16) & 0xFFFF;
}


// PIC remapping
void pic_remap()
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);

    outb(0x21, 0x20);
    outb(0xA1, 0x28);

    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    outb(0x21, 0x0);
    outb(0xA1, 0x0);  
}


// Load IDT
extern "C" void load_idt(uint32_t);


// Initialize IDT
extern "C" void idt_init()
{
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    for(int i=0;i<256;i++)
        set_idt_gate(i, 0);

    pic_remap();

    // keyboard interrupt = IRQ1 = IDT entry 33
    set_idt_gate(33, (uint32_t)keyboard_asm_handler);

    load_idt((uint32_t)&idtp);

    asm volatile("sti");
}
