global loader
     MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
     FLAGS        equ 0x0            ; multiboot flags
     CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum

KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes

    section .bss
        align 4                                     ; align at 4 bytes
        kernel_stack:                               ; label points to beginning of memory
            resb KERNEL_STACK_SIZE                  ; reserve stack for the kernel
        
        section .text:                  ; start of the text (code) section
        align 4                         ; the code must be 4 byte aligned
            dd MAGIC_NUMBER            ; write the magic number to the machine code,
            dd FLAGS                   ; the flags,
            dd CHECKSUM                ; and the checksum     

        loader:
            mov esp, kernel_stack + KERNEL_STACK_SIZE   ; point esp to the start of the     
        extern kmain
        call kmain

        .loop:
            jmp .loop

times 510 - ($ - $$) db 0   ; Fill the rest of the boot sector with zeros up to 510 bytes

dw 0xAA55   ; Boot sector signature, required to make the disk bootable