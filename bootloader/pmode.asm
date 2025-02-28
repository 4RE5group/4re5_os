[BITS    32]

pmode:
        mov     ax, DATASEG

        ;Setup Data Again
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax

        ;Setup x86 Stack
        mov     ebp, 0x90000
        mov     esp, ebp
        mov     ss, ax

        jmp     KERNEL