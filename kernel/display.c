#include "include/display.h"
#include "include/font.h"

void IntToString(int value, char* buffer)
{
    char temp[11];
    int i = 0;
    int isNegative = 0;

    if (value < 0) 
    {
        isNegative = 1;
        value = -value;
    }

    do 
    {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    } while (value > 0);

    if (isNegative) 
    {
        temp[i++] = '-';
    }

    temp[i] = '\0';

    int j;

    for (j = 0; j < i; j++) 
    {
        buffer[j] = temp[i - j - 1];
    }

    buffer[j] = '\0';
}

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