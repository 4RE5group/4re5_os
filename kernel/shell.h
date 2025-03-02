#include "include/keyboard.h"

void handle_shell() {
    int start_x=10;
    int start_y=50;

    int cursor_line = start_y;
    int cursor_col = 0;

    char* pwd = "root@4re5> ";
    int afterPWD = start_x+10+sizeof(pwd)*25;

    BYTE key;
    char c;

    while(1) {
        draw_text(pwd, start_x, cursor_line, COLOR_YELLOW);
        key = getKeyPress();
        

        switch(key) {
            case 0: // no key
                continue;

            case KEY_ENTER:
                cursor_col=afterPWD;
                cursor_line+=FONT_HEIGHT;
                continue;
            
            case KEY_BACKSPACE:
                if(cursor_col > 0) {
                    cursor_col--;
                    draw_rectangle(afterPWD+cursor_col, cursor_line, FONT_WIDTH, FONT_HEIGHT, COLOR_BLACK);
                }
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
        cursor_col+=FONT_WIDTH;
        while(getKeyPress() == key) {}
    }
}