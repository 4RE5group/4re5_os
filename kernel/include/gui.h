#include "images/start.h"
#include "images/close.h"

void TaskbarDraw() {
    // Draw the taskbar
    BYTE backColor = 0x0F - get_pixel(0, 0);
    draw_rectangle(0, 0, SCREEN_WIDTH, 25, backColor);
    
    // start icon
    draw_image(start, 5, 5, 15, 15);
}

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


void draw_window(Window* window) {
    // Open the window
    int border = 3;
    draw_rectangle(window->x-border, window->y-border, window->x + window->width+border, window->y + window->height+border, COLOR_DARKGREY);
    draw_rectangle(window->x, window->y, window->x + window->width, window->y + window->height, window->color);

    window->focus = 1;

    draw_text(window->title, window->x+5, window->y, COLOR_BLUE);

    draw_image(close, window->x + window->width, window->y, 15, 15);
}