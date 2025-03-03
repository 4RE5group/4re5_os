#!/bin/bash

# debug
# g++ kernel/main.c -o bin/test && ./bin/test

OUTPUT="./bin"
PATH="$(pwd)/toolchain/bin:$PATH"
OS_NAME="4re5_os"
VERSION="1.1"
FINAL_FILE="$OS_NAME-$VERSION.img"
COLOR_ERROR="\e[31m"
COLOR_GREEN="\e[32m"
COLOR_RESET="\e[0m"
# Clear OUTPUT directory
rm -rf $OUTPUT/*
mkdir -p $OUTPUT

clear

echo "4re5 group - compiling..."

echo "COMPILING ASM BOOTLOADER"
nasm -fbin bootloader/boot.asm -o $OUTPUT/boot.bin || exit 1
nasm -felf kernel/entry.asm -o $OUTPUT/entry.out || exit 1
nasm -felf kernel/idt/idt.asm -o $OUTPUT/asmidt.o || exit 1

echo "COMPILING C KERNEL"
i686-linux-gnu-gcc -fno-pic -ffreestanding -m32 -g -c kernel/main.c -o $OUTPUT/kernel.o || exit 1
i686-linux-gnu-gcc -fno-pic -ffreestanding -m32 -g -c kernel/mouse.c -o $OUTPUT/mouse.o || exit 1
i686-linux-gnu-gcc -fno-pic -ffreestanding -m32 -g -c kernel/idt/idt.c -o $OUTPUT/idt.o || exit 1
i686-linux-gnu-gcc -fno-pic -ffreestanding -m32 -g -c kernel/mem/mem.c -o $OUTPUT/mem.o || exit 1
i686-linux-gnu-gcc -fno-pic -ffreestanding -m32 -g -c kernel/timer.c -o $OUTPUT/timer.o || exit 1
i686-linux-gnu-gcc -fno-pic -ffreestanding -m32 -g -c kernel/display.c -o $OUTPUT/display.o || exit 1
i686-linux-gnu-gcc -fno-pic -ffreestanding -m32 -g -c kernel/io.c -o $OUTPUT/io.o || exit 1
i686-linux-gnu-gcc -fno-pic -ffreestanding -m32 -g -c kernel/font.c -o $OUTPUT/font.o || exit 1


echo "LINKING WHOLE OS"
i686-linux-gnu-ld -m elf_i386 -Ttext 0x7E00 --oformat binary -nostdlib \
    -o $OUTPUT/fullkernel.bin $OUTPUT/entry.out $OUTPUT/*.o || exit 1


echo "MOUNTING IMG ==> $FINAL_FILE"
cat $OUTPUT/boot.bin $OUTPUT/fullkernel.bin > "$FINAL_FILE" || exit 1


qemu-system-i386 -net nic,model=rtl8139 -net user \
    -drive format=raw,file="$FINAL_FILE"  #  -s -S