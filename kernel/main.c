#include "include/display.h"
#include "include/stdint.h"
#include "shell.h"
#include "include/images/background.h"
#include "include/gui.h"
#include "idt/idt.h"

int main()
{
    // draw background
    // draw_image(background, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // draw_text("4re5 Group", 10, 10, COLOR_LIGHTRED);
    TaskbarDraw();
    
    SetupIDT();
    InitMouse();
    InitTimer();

    // BYTE key;
    // while(1) {
    //     key = getKeyPress();

    //     if(key == KEY_ESC){                             //x  y    w    h  state focus
    //         Window win1 = { "Window Name1", COLOR_CYAN, 100, 100, 100, 100, 1, true, 0, 0, 0 };
    //         draw_window(&win1);
    //     }

    //     while(key == getKeyPress()){}
    // }
    handle_shell();
    return 0;
}

