#include <stdint.h>

extern "C" void idt_init();

extern "C" void kernel_main()
{
    volatile unsigned short* vga = (unsigned short*)0xB8000;

    const char* msg = "VOS Kernel Started";
    int i = 0;

    while(msg[i])
    {
        vga[i] = (unsigned short)msg[i] | (0x0F << 8);
        i++;
    }

    // initialize interrupt system
    idt_init();

    // kernel loop
    while(1)
    {
        asm volatile("hlt");  
    }
}
