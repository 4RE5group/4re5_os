BITS 16
org 0x1000

section .text
    global _start

_start:
    mov ah, 0x0E
    mov al, 'L' ; boot ending char
    int 0x10


    ; Load the kernel (sector 3 onwards) into memory at 0x2000
    mov bx, 0x2000         ; Address to load the kernel
    mov dl, 0x80           ; Drive number (0x80 for the first hard disk)
    mov si, 0x01           ; Number of sectors to load (adjust as needed)
    call load_kernel

    mov ah, 0x0E
    mov al, 'o' ; boot ending char
    int 0x10

    ; Switch to protected mode and jump to kernel entry point
    call enter_protected_mode

    mov eax, cr0         ; Load the contents of CR0 into EAX
    test eax, 1          ; Check if the Protection Enable (PE) bit is set
    jz real_mode         ; Jump if PE is 0 (Real Mode)

    ; Kernel entry point at 0x2000
    ; jmp 0x08:0x2000        ; Far jump: CS=0x08 (kernel code segment), IP=0x2000
    ; hlt

protected_mode:
    ; Code to handle protected mode
    mov eax, 0x1         ; Example: Set EAX to 1 for Protected Mode
    hlt

real_mode:
    ; Code to handle real mode
    mov eax, 0x0         ; Example: Set EAX to 0 for Real Mode
    hlt

; Function to load kernel
load_kernel:
    mov ah, 0x02           ; BIOS read sectors function
    mov al, 1              ; Number of sectors to read
    mov ch, 0              ; Cylinder number
    mov cl, 3              ; Start reading from sector 3
    mov dh, 0              ; Head number
    int 0x13               ; Call BIOS interrupt
    jc load_error          ; Jump if carry flag is set (error)
    add bx, 0x200          ; Move destination pointer
    dec si                 ; Decrement sector counter
    jnz load_kernel        ; Continue if sectors remain
    ret

load_error:
    mov ah, 0x0E
    mov al, '!'
    int 0x10
    cli
    hlt

enter_protected_mode:
    ; Disable interrupts
    cli

    ; Load GDT
    lgdt [gdt_descriptor]

    ; Enable protected mode
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    ; Return in protected mode
    ret

; Global Descriptor Table (GDT)
gdt:
    dq 0x0                 ; Null descriptor
    dq 0x00CF9A000000FFFF  ; Code segment descriptor
    dq 0x00CF92000000FFFF  ; Data segment descriptor

gdt_descriptor:
    dw gdt - gdt - 1       ; Size of GDT
    dd gdt                 ; Address of GDT