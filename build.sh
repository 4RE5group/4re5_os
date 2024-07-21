C_OUTPUT="kmain.o"
GCC_FLAGS="-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Werror"

# clean
clear
rm -rf os.iso kernel.elf *.o


# build kernel
nasm -f elf loader.s -o loader.o
nasm -f elf io.s -o io.o
# c code
gcc $GCC_FLAGS -c src/kmain.c -o $C_OUTPUT
gcc $GCC_FLAGS -c src/framebuffer.c -o framebuffer.o
gcc $GCC_FLAGS -c src/serial_port.c -o serial_port.o


# link kernel
ld -T link.ld -melf_i386 *.o -o kernel.elf

# move kernel
cp kernel.elf iso/boot/kernel.elf

# build iso
genisoimage -R\
            	-b boot/grub/stage2_eltorito   \
            	-no-emul-boot                       \
            	-boot-load-size 4                   \
            	-A os                               \
            	-input-charset utf8                 \
            	-quiet                              \
            	-boot-info-table                    \
            	-o os.iso                           \
             	iso

# emulate
bochs -f bochsrc.txt -q