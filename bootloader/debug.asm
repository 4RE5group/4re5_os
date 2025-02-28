; debuging file


print_string:
    pusha
.loop:
    lodsb                  ; Load next character from SI into AL
    or al, al              ; Check if AL is zero (end of string)
    jz .done               ; jump to finish
    mov bx, 0x0007         ; color
    mov ah, 0x0E           ; BIOS Teletype function
    int 0x10               ; Print character
    jmp .loop
.done:
    popa
    ret

;640x480 screen
branding_msg db "4re5 os - 4re5 group 2025   ", 0

booting_msg db "Booting OS...   ", 0

pmode_msg db "Entering Protected Mode...   ", 0

test_msg db 'GDT OK', 0
