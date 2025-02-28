global outb             ; make the label outb visible outside this file

                            ; outb - send a byte to an I/O port
                            ; stack: [esp + 8] the data byte
                            ; [esp + 4] the I/O port
                            ; [esp    ] return address
    outb:
        mov al, [esp + 8]   ; move the data to be sent into the al register
        mov dx, [esp + 4]   ; move the address of the I/O port into the dx register
        out dx, al          ; send the data to the I/O port
        ret


global inb

    ; inb - returns a byte from the given I/O port
    ; stack: [esp + 4] The address of the I/O port
    ;        [esp    ] The return address
    inb:
        mov dx, [esp + 4]       ; move the address of the I/O port to the dx register
        in  al, dx              ; read a byte from the I/O port and store it in the al register
        ret                     ; return the read byte


global bios_interrupt
    ; 1st arg 1 byte -> function number
    ; 2nd arg 1 byte -> char 
    bios_interrupt:
        mov ah, 0x0e    ; function number = 0x0e : Display Character
        mov al, '!'     ; AL = code of character to display
        int 0x10        ; call INT 10h, BIOS video service