#include "stdint.h"
#include "font.h"

#define SCREEN_WIDTH 640 //640x480
#define SCREEN_HEIGHT 480
#define VIDEO_MEM_OFFSET 0xFD000000

// remove to text in qemu + prod
// #define DEBUG 1

#ifdef DEBUG
#include <stdio.h>
#endif // DEBUG
 
#define COLOR_BLACK          0x00
#define COLOR_BLUE           0x01
#define COLOR_GREEN          0x02
#define COLOR_CYAN           0x03
#define COLOR_RED            0x04
#define COLOR_MAGENTA        0x05
#define COLOR_ORANGE         0x06
#define COLOR_GREY           0x07
#define COLOR_DARKGREY       0x08
#define COLOR_PURPLE         0x09
#define COLOR_LIME           0x0A
#define COLOR_DARKGRAYGREEN  0x0B
#define COLOR_LIGHTRED       0x0C
#define COLOR_PINK           0x0D
#define COLOR_YELLOW         0x0E
#define COLOR_WHITE          0x0F

BYTE get_pixel(int x, int y) {
    LPBYTE framebuffer = (LPBYTE)VIDEO_MEM_OFFSET;
    return framebuffer[y * SCREEN_WIDTH + x];
}

void set_pixel(int x, int y, BYTE color) {
    LPBYTE framebuffer = (LPBYTE)VIDEO_MEM_OFFSET;
    framebuffer[y * SCREEN_WIDTH + x] = color;
}

void draw_image(BYTE* image, int SCREEN_X, int SCREEN_Y, int width, int height) {
    BYTE color;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            color = image[width * y + x];  // Correct indexing
            set_pixel(SCREEN_X + x, SCREEN_Y + y, color);
        }
    }
}

void draw_rectangle(int x, int y, int w, int h, BYTE color) {
    int x2=x+w;
    int y2=y+h;
    for (int j=y; j<y2; j++) {
        for (int i=x; i<x2; i++) {
            set_pixel(i, j, color);
        }
    }
}

void clear_screen(BYTE color) {
    draw_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
}


void draw_char(char c, int x, int y, BYTE color) {
    if(!font) {
        draw_rectangle(SCREEN_WIDTH-10, SCREEN_HEIGHT-10, 10, 10, COLOR_RED);
        return;
    }

    int offset = 17 + ((int)c) * 16;
    
    BYTE byte;
    for (int row = 0; row < 16; row++) {
        byte = font[offset + row];

        for (int col = 0; col < 8; col++) {
            if ((byte >> (7-col)) & 1) {
                set_pixel(x+col, y+row, color);
            }
        }
    }
}

void draw_text(char* text, int x, int y, BYTE color) {
    int font_padding = 2;
    char c;
    int charpos_x=x;
    int charpos_y=y;
    for (int i = 0; text[i] != '\0'; i++) {  // Corrected: sizeof(text) does not give the string length
        c = text[i];
        // do not escape screen, add new lines
        if ((c == '\n' || charpos_x+8<=charpos_x) && charpos_y+16<=SCREEN_HEIGHT) {
            charpos_y++;
        }

        draw_char(c, charpos_x, charpos_y, color);
        charpos_x+=8+font_padding;
    }
}