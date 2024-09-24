OUTPUT="./bin"
FLAGS="-g -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -Wall -O0 -Iinc"
FINAL_FILE="OS.elf"

COLOR_ERROR="\e[31m"
COLOR_GREEN="\e[32m"
COLOR_RESET="\e[0m"


clear

# clear OUTPUT
rm -rf $OUTPUT/*

# compile bootloader
nasm -f elf64 boot.asm -o $OUTPUT/boot.o
#compile io
nasm -f elf64 kernel/io.asm -o $OUTPUT/io.o

# compile kernel C
if ! gcc -I./kernel $FLAGS -std=gnu99 -c ./kernel/main.c -o $OUTPUT/kernel_main.o; then
    echo -e "$COLOR_ERROR[x] kmain compile error$COLOR_RESET"
    exit
fi
if ! gcc -I./kernel $FLAGS -std=gnu99 -c ./kernel/framebuffer.c -o $OUTPUT/kernel_framebuffer.o; then
    echo -e "$COLOR_ERROR[x] framebuffer compile error$COLOR_RESET"
    exit
fi

# link kernel
# if ! ld -g -nostdlib -relocatable bin/*.o -o $OUTPUT/kernel.o; then
#     echo -e "$COLOR_ERROR[x] linking to kernel.o error$COLOR_RESET"
#     exit
# fi
# convert kernel to bin format
# if ! gcc $FLAGS -nostdlib -nodefaultlibs -T link.ld -o $OUTPUT/kernel.bin $OUTPUT/completeKernel.o; then
#     echo -e "$COLOR_ERROR[x] error converting completeKernel.o > kernel.bin$COLOR_RESET"
#     exit
# fi

# assemble whole OS
ld -T link.ld -melf_x86_64 $OUTPUT/*.o -o $OUTPUT/$FINAL_FILE
# if ! dd if=$OUTPUT/boot.o >> $OUTPUT/$FINAL_FILE && \
# dd if=$OUTPUT/kernel.o >> $OUTPUT/$FINAL_FILE && \
# dd if=/dev/zero bs=512 count=8 >> $OUTPUT/$FINAL_FILE; then
#     echo -e "$COLOR_ERROR[x] error assembling whole OS$COLOR_RESET"
#     exit
# fi



# emulate for testing 
echo -e "$COLOR_GREEN[o] Compilated successfully$COLOR_RESET"
qemu-system-x86_64 bin/$FINAL_FILE
# -monitor stdio