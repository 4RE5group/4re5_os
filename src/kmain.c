#include "framebuffer.h"
#include "serial_port.h"

void drawPixel(int x, int y) {
    unsigned short address = 0xA0000 + y * 320 + x;
    // soon will be added
}

void kmain()
{
    char text[] = "4re5 os - V1.0";
    fb_write(text, sizeof(text));

    serial_write(SERIAL_COM1_BASE, text, sizeof(text));
}
