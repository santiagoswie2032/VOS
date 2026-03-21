
set -e

echo " Building VOS..."

cd ..
rm -rf build iso VOS.iso

mkdir -p build
mkdir -p iso/boot/grub


nasm -f bin bootloader/boot.asm -o build/boot.bin


i686-elf-g++ -ffreestanding -c kernel/kernel.cpp -o build/kernel.o
i686-elf-g++ -ffreestanding -c kernel/arch/idt.cpp -o build/idt.o
i686-elf-g++ -ffreestanding -c kernel/drivers/keyboard.cpp -o build/keyboard.o


nasm -f elf32 kernel/arch/interrupt.asm -o build/interrupt.o


i686-elf-ld -T linker.ld -o build/kernel.bin \
build/kernel.o build/idt.o build/keyboard.o build/interrupt.o

cat > iso/boot/grub/grub.cfg << EOF
set timeout=0
set default=0

menuentry "VOS" {
    multiboot /boot/kernel.bin
    boot
}
EOF

cp build/kernel.bin iso/boot/kernel.bin

grub-mkrescue -o VOS.iso iso

echo "Running VOS..."
qemu-system-i386 -cdrom VOS.iso