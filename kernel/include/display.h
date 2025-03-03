#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "stdint.h"

#define SCREEN_WIDTH 640 //640x480
#define SCREEN_HEIGHT 480
#define VIDEO_MEM_OFFSET 0xFD000000

 
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

void IntToString(int value, char* buffer);
BYTE get_pixel(int x, int y);
void set_pixel(int x, int y, BYTE color);
void draw_image(BYTE* image, int SCREEN_X, int SCREEN_Y, int width, int height);
void draw_rectangle(int x, int y, int w, int h, BYTE color);
void clear_screen(BYTE color);
void draw_char(char c, int x, int y, BYTE color);
void draw_text(char* text, int x, int y, BYTE color);


typedef struct
{
    char* title;
    BYTE color;

    int x, y;
    int width, height;

    int state; //0 = minimized, 1 = normal, 2 = maximized
    int focus;

    int isDragging;

    int dragOffsetX;
    int dragOffsetY;

    int isMaximized;

    int orgX, orgY;
    int orgW, orgH;
} Window;

#endif // DISPLAY_H