okay so when we turn on your pc, the cpu wakes up briefly and it loads up the first 512 bytes which is the bootloader. Bootloader then loads the kernel
the kernel wakes up the cpu properly, manages memory, wakes up OS, kernel is basically the bridge or the translator between cpu and other hardware components to OS.
setting up kernel and its files : 
1. kernel.cpp : reesponsible for 1. entry point (kernel_main) , 2. calls idt_init() , 3. triggers a test interrupt
so kernel.cpp is basically like the brain of the kernel

2. idt.hpp : defines how the interrupt descripter table (IDT) looks in the memory , it dosent have any logic and just structures

3. idt.cpp : creates the interrupt descripter table (IDT), loads it with lidt. its like a interrupt wiring.

4. interrupt.asm : the bridge between CPU and C++ , it saves registers and returns with iret 
