#include "include/stdint.h"
#include "idt/idt.h"
#include "include/io.h"
#include "include/display.h"

#include "include/timer.h"

int ticks = 0;
int seconds = 0; 
int minutes = 0;
int drawBar = false;

void PITIRQ0()
{
    ticks += 1;

    if (ticks % 20 == 0)
    {
        seconds++;
    }
}

void Sleep(int seconds)
{
    int startTick = ticks;

    while (ticks < startTick + (startTick * (seconds * 10)))
    {}
}

void DrawLoadBar()
{
    while (seconds % 10 != 0)
    {
        int totaltime = 10;
        int timeleft = totaltime - seconds;

        int wbar = (seconds * 100) / totaltime;

        for (int y = 0; y < 16; y++)
        {
            for (int x = 0; x < wbar; x++)
            {
                set_pixel(x + (SCREEN_WIDTH / 2 - 38), y + (SCREEN_HEIGHT / 2 + 70), 0x30);
            }
        }
    }
}

void InitTimer(void)
{
    IRQInstallHandler(0x00, &PITIRQ0);

    DWORD divisor = 1193180 / 100;

    outb(0x43, 0x36);
    outb(0x40, (BYTE)(divisor & 0xFFFF));
    outb(0x40, (BYTE)((divisor & 0xFFFF) & 0xFF));
}