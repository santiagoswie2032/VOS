#include <stdint.h>

// Read from hardware port
unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// VGA text buffer
volatile unsigned short* vga = (unsigned short*)0xB8000;
int cursor = 0;


// Simple scancode → ASCII map
unsigned char kbd_map[128] = {
0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
'\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
0,'a','s','d','f','g','h','j','k','l',';','\'','`',
0,'\\','z','x','c','v','b','n','m',',','.','/',
0,'*',0,' ',
};


// Called from interrupt.asm
extern "C" void keyboard_handler()
{
    unsigned char scancode = inb(0x60);

    // ignore key releases
    if(scancode & 0x80)
        return;

    char c = kbd_map[scancode];

    if(c)
    {
        vga[cursor++] = (unsigned short)c | (0x0F << 8);
    }
}