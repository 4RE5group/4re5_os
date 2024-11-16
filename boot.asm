;16-bit Bootloader to Load and Execute a 32-bit Kernel
BITS 16
org 0x7C00
section .text
    global _start

_start:
    mov ah, 0x0E
    mov al, 'L'
    int 0x10
    mov al, 'o'
    int 0x10
    mov al, 'a'
    int 0x10
    mov al, 'd'
    int 0x10
    mov al, 'i'
    int 0x10
    mov al, 'n'
    int 0x10
    mov al, 'g'
    int 0x10

    ; Set up the stack
    xor ax, ax
    mov ss, ax             ; Set stack segment to 0
    mov sp, 0x7C00         ; Set stack pointer to top of the boot sector

    ; Load the second sector (loader) into memory at 0x1000
    mov bx, 0x1000
    mov dl, 0x80       ; Drive number (0x80 for the first hard disk)
    call load_sector


    mov ah, 0x0E
    mov al, 'A' ; boot ending char
    int 0x10

    ; Jump to the loaded code at 0x1000
    jmp 0x1000


    mov ah, 0x0E
    mov al, 'Z' ; boot ending char
    int 0x10
    hlt ; finished

load_sector: ;load sector from disk
    mov ah, 0x02       ; BIOS read sectors function
    mov al, 0x01       ; Number of sectors to read
    mov ch, 0x00       ; Cylinder number
    mov cl, 0x02       ; Sector number (2nd sector, which is loader)
    mov dh, 0x00       ; Head number
    int 0x13           ; Call BIOS interrupt
    jc load_error      ; Jump if carry flag is set (error)
    ret                ; Return if successful

load_error:
    mov ah, 0x0E
    mov al, '-' ; ERROR flag
    int 0x10
    cli                     ; Disable interrupts
    hlt                     ; Halt the CPU
; Boot sector signature
times 510 - ($ - $$) db 0
dw 0xAA55
