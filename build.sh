#!/bin/bash

OUTPUT="./bin"
FLAGS="-ffreestanding -fno-pic -nostdlib -nostartfiles -m32" 

OS_NAME="4re5_os"
FINAL_FILE="$OS_NAME.bin"

COLOR_ERROR="\e[31m"
COLOR_GREEN="\e[32m"
COLOR_RESET="\e[0m"
arch_format="x86_64"  # Change to x86_64
format="elf64"

# Clear OUTPUT directory
rm -rf $OUTPUT/*
mkdir -p $OUTPUT
clear
# dd if=/dev/zero of=disk.img bs=512 count=2880 seek=0 conv=notrunc

# Compile bootloader (if needed, depends on if you use a separate boot.asm)
nasm -f bin boot.asm -o $OUTPUT/boot.bin || exit 1
nasm -f bin kernel/loader.asm -o $OUTPUT/loader.bin || exit 1

# Compile kernel files
gcc -m32 -ffreestanding -c kernel/main.c -o $OUTPUT/kernel.o -e kmain || exit 1

ld -m elf_i386 -e kmain -Ttext 0x2000 $OUTPUT/kernel.o -o $OUTPUT/kernel.elf || exit 1
objcopy -O binary $OUTPUT/kernel.elf $OUTPUT/kernel.bin || exit 1

# Link kernel object files into a single ELF
dd if=$OUTPUT/boot.bin of=disk.img bs=512 count=1  # Create a blank disk image
dd if=$OUTPUT/loader.bin of=disk.img bs=512 seek=1 count=1
dd if=$OUTPUT/kernel.bin of=disk.img bs=512 seek=2
# dd if=$OUTPUT/boot.bin of=disk.img bs=512 seek=0 conv=notrunc
# dd if=$OUTPUT/kernel.bin of=disk.img bs=512 seek=1 conv=notrunc

# ld -m elf_x86_64 -o $OUTPUT/$FINAL_FILE -Ttext 0x1000 $OUTPUT/boot.o $OUTPUT/kernel_main.o || exit 1
# ld -m elf_i386 -Ttext 0x1000 $OUTPUT/boot.o $OUTPUT/kernel_main.o -o $OUTPUT/kernel.bin --oformat binary
# ld -m elf_x86_64 -o $OUTPUT/$FINAL_FILE --entry=_start $OUTPUT/boot.o $OUTPUT/kernel_main.o || exit 1
# ld -m elf_x86_64 -o $OUTPUT/$FINAL_FILE $OUTPUT/*.o || exit 1

# make disk
# dd if=$OUTPUT/$FINAL_FILE of=disk.img bs=512 count=2880



# Set permissions for output files
chmod 777 $OUTPUT/*

echo -e "$COLOR_GREEN[o] Compiled successfully$COLOR_RESET"

# Test the kernel with QEMU
qemu-system-x86_64 -drive file=disk.img,format=raw --no-reboot --no-shutdown -m 2048 -vga std -d int
# qemu-system-x86_64 -kernel $OUTPUT/$FINAL_FILE -m 2048 -vga std --no-reboot --no-shutdown -machine type=pc-i440fx-3.1 || exit 1