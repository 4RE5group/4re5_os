[BITS    16]
[ORG 0x7C00]

%define KERNEL 0x7E00

BootMain:
        ;Setup Data
        cli
        cld

        xor     ax, ax
        mov     ds, ax
        mov     es, ax

        ;Setup Stack
        mov     sp, 0x7C00
        mov     ss, ax

        sti

        ;Setup VESA (640x480 8bpp)
        mov     ax, 0x4F02
        mov     bx, 0x4101
        int     0x10

        

        call    ReadSectors
        call    SetupGDT

        jmp     CODESEG:pmode

;---------------------------------------

ReadSectors:
        mov     cx, 10      ; counter

.loop:
        push    cx

        mov     ah, 0x42
        mov     si, DAP
        int     0x13

        add dword [DAP + 8], 127
        add word  [DAP + 6], 0xFE0

        pop cx

        loop .loop

        ret

align 4

DAP:
        db      0x10        ;DAP     byte [dap+0]
        db      0x00        ;Unused  byte [dap+1]
        dw      0x7F        ;Sectors byte [dap+2]
        dw      0x0000      ;Segment byte [dap+3] byte [dap+4]
        dw      KERNEL >> 4 ;Offset  word [DAP+6]
        dq      1           ;LBA      word [DAP+8]

;---------------------------------------

%include "bootloader/gdt.asm"
%include "bootloader/pmode.asm"
%include "bootloader/debug.asm"

times 510 - ($ - $$) db 0x00
dw 0xAA55