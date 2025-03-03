#include "include/keyboard.h"
#include "include/display.h"
#include "include/font.h"

void handle_shell() {
    BYTE backgroundColor = COLOR_BLACK;
    BYTE pwdColor = COLOR_YELLOW;
    BYTE textColor = COLOR_WHITE;

    clear_screen(backgroundColor);

    int start_x=10;
    int start_y=4*FONT_HEIGHT;

    int cursor_line = start_y;
    int cursor_col = 0;

    char* pwd = "root@4re5> "; // length of 12
    char* motd = "";
    int afterPWD = start_x+FONT_WIDTH*(12+1);

    // draw motd
    draw_text("    4re5 os", 10, 10, COLOR_LIGHTRED);
    draw_text("credits:  4re5 group (2025)", 10, 10+FONT_HEIGHT, COLOR_LIGHTRED);
    draw_text("type 'help' to get started", 10, 10+2*FONT_HEIGHT, COLOR_LIGHTRED);


    BYTE key;
    char c;
    int charpos=0;
    char* command[64];

    while(1) {
        // draw pwd
        draw_text(pwd, start_x, cursor_line, COLOR_YELLOW);
        key = getKeyPress();
        

        switch(key) {
            case 0: // no key
                continue;

            case KEY_ENTER:
                cursor_col=0;
                cursor_line+=FONT_HEIGHT;
                while(key == getKeyPress()) {}
                continue;
            
            case KEY_BACKSPACE:
                if(cursor_col > 0) {
                    charpos--;
                    cursor_col-=FONT_WIDTH;
                    draw_rectangle(afterPWD+cursor_col, cursor_line, FONT_WIDTH, FONT_HEIGHT, backgroundColor);
                }
                while(key == getKeyPress()) {}
                continue;
            
            case KEY_LSHIFT:
            case KEY_RSHIFT:
                c = uppercase[key][0];
                break;
            default: // other chars
                c = lowercase[key][0];
                break;
        }
        draw_char(c, afterPWD+cursor_col, cursor_line, COLOR_WHITE);
        charpos++;
        command[charpos] = c;
        cursor_col+=FONT_WIDTH;
        while(getKeyPress() == key) {}
    }
}