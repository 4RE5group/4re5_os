#include "include/stdint.h"
#include "include/io.h"
#include "idt/idt.h"
#include "include/display.h"
#include "include/timer.h"

#include "include/cursor.h"
#include "include/mouse.h"

extern Window* window;

BYTE MouseArea[CURSOR_WIDTH * CURSOR_HEIGHT];
BYTE MouseCursorAfter[CURSOR_WIDTH * CURSOR_HEIGHT];
BYTE MousePrevious[CURSOR_WIDTH * CURSOR_HEIGHT];

BYTE mouseData;
BYTE mouseCycle;
BYTE mousePacket[4];

int mousePressed = 0;

int prevMouseX = 0;
int prevMouseY = 0;

int mouseX = 0;
int mouseY = 0;

void GetMouseState(int* x, int* y, int* pressed) 
{
    *x = mouseX;
    *y = mouseY;
    *pressed = mousePressed;
}

void DrawMouse(BYTE color)
{
    for (int y = 0; y < CURSOR_HEIGHT; y++)
    {
        int x = 0;

        for (int i = 0; i < 2; i++)
        {
            BYTE byte = cursor[y * 2 + i];

            for (int j = 7; j >= 0; j--)
            {
                if (byte & (1 << j))
                {
                    set_pixel(mouseX + x, mouseY + y, color);
                }
                x++;
            }
        }
    }
}

void SaveMouseArea()
{
    for (int y = 0; y < CURSOR_HEIGHT; y++)
    {
        for (int x = 0; x < CURSOR_WIDTH; x++)
        {
            BYTE color = get_pixel(mouseX + x, mouseY + y);

            MouseArea[y * CURSOR_WIDTH + x] = color;
        }
    }
}

void SavePreviousArea(int prevMouseX, int prevMouseY)
{
    for (int y = 0; y < CURSOR_HEIGHT; y++)
    {
        for (int x = 0; x < CURSOR_WIDTH; x++)
        {
            MousePrevious[y * CURSOR_WIDTH + x] = get_pixel(prevMouseX + x, prevMouseY + y);
        }
    }
}

void RestorePreviousCursor()
{
    for (int y = 0; y < CURSOR_HEIGHT; y++)
    {
        for (int x = 0; x < CURSOR_WIDTH; x++)
        {
            set_pixel(mouseX + x, mouseY + y, MouseArea[y * CURSOR_WIDTH + x]);
        }
    }
}

void MouseWait()
{
    while (inb(0x64) & 0x02);
}

void ClearTrails(int prevMouseX, int prevMouseY)
{
    for (int y = 0; y < CURSOR_HEIGHT; y++)
    {
        for (int x = 0; x < CURSOR_WIDTH; x++)
        {
            set_pixel(prevMouseX + x, prevMouseY + y, MouseArea[y * CURSOR_WIDTH + x]);
        }
    }
}

void MouseHandler()
{
    mouseData = inb(0x60);

    if (mouseCycle == 0 && !(mouseData & 0x08))
    {
        return;
    }
    
    mousePacket[mouseCycle++] = mouseData;

    if (mouseCycle == 3)
    {
        mouseCycle = 0;

        mousePressed = (mousePacket[0] & 0x1);

        int deltaX = (int)((char)mousePacket[1]);
        int deltaY = (int)((char)mousePacket[2]);

        int prevMouseX = mouseX;
        int prevMouseY = mouseY;

        mouseX += deltaX;
        mouseY -= deltaY;

        mouseX = (mouseX < 0) ? 0 : ((mouseX > SCREEN_WIDTH - 16) ? SCREEN_WIDTH - 16 : mouseX);
        mouseY = (mouseY < 0) ? 0 : ((mouseY > SCREEN_HEIGHT - 16) ? SCREEN_HEIGHT - 16 : mouseY);

        //HandlewindowDragging(window, mouseX, mouseY, mousePressed);

        ClearTrails(prevMouseX, prevMouseY);
        SaveMouseArea();
        RestorePreviousCursor(prevMouseX, prevMouseY);
        DrawMouse(0x1E);
    }
}

void InitMouse()
{
    outb(0x64, 0xA7);
    outb(0x64, 0xA8);

    while (inb(0x64) & 1)
    {
        inb(0x60);
    }

    IRQInstallHandler(12, &MouseHandler);

    outb(0x64, 0x20);
    BYTE status = (inb(0x60) | 2);
    outb(0x64, 0x60);
    outb(0x60, status);

    outb(0x64, 0xD4);
    outb(0x60, 0xF4);
}