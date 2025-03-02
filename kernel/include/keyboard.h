#include "io.h"

char commandBuffer[50];
int commandLength = 0;

const char* lowercase[] = {
    " ", " ", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "-", "=", "\b", " ", "q", "w", "e", "r", "t", "y", "u", "i",
    "o", "p", "[", "]", "\n", " ", "a", "s", "d", "f", "g", "h",
    "j", "k", "l", ";", "'", "`", " ", "\\", "z", "x", "c", "v",
    "b", "n", "m", ",", ".", "/", " ", "*", " ", " "
};

const char* uppercase[] = {
    " ", " ", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")",
    "_", "+", "\b", " ", "Q", "W", "E", "R", "T", "Y", "U", "I",
    "O", "P", "{", "}", "\n", " ", "A", "S", "D", "F", "G", "H",
    "J", "K", "L", ":", "\"", "~", " ", "|", "Z", "X", "C", "V",
    "B", "N", "M", "<", ">", "?", " ", " ", " ", " "
};

#define KEY_ESC    0x01
#define KEY_1      0x02
#define KEY_2      0x03
#define KEY_3      0x04
#define KEY_4      0x05
#define KEY_5      0x06
#define KEY_6      0x07
#define KEY_7      0x08
#define KEY_8      0x09
#define KEY_9      0x0A
#define KEY_0      0x0B
#define KEY_MINUS  0x0C
#define KEY_EQUAL  0x0D
#define KEY_BACKSPACE  0x0E
#define KEY_TAB    0x0F
#define KEY_Q      0x10
#define KEY_W      0x11
#define KEY_E      0x12
#define KEY_R      0x13
#define KEY_T      0x14
#define KEY_Y      0x15
#define KEY_U      0x16
#define KEY_I      0x17
#define KEY_O      0x18
#define KEY_P      0x19
#define KEY_LBRACKET  0x1A
#define KEY_RBRACKET  0x1B
#define KEY_ENTER  0x1C
#define KEY_CTRL   0x1D
#define KEY_A      0x1E
#define KEY_S      0x1F
#define KEY_D      0x20
#define KEY_F      0x21
#define KEY_G      0x22
#define KEY_H      0x23
#define KEY_J      0x24
#define KEY_K      0x25
#define KEY_L      0x26
#define KEY_SEMICOLON  0x27
#define KEY_APOSTROPHE 0x28
#define KEY_GRAVE  0x29
#define KEY_LSHIFT 0x2A
#define KEY_BACKSLASH 0x2B
#define KEY_Z      0x2C
#define KEY_X      0x2D
#define KEY_C      0x2E
#define KEY_V      0x2F
#define KEY_B      0x30
#define KEY_N      0x31
#define KEY_M      0x32
#define KEY_COMMA  0x33
#define KEY_DOT    0x34
#define KEY_SLASH  0x35
#define KEY_RSHIFT 0x36
#define KEY_KP_MULTIPLY  0x37
#define KEY_ALT    0x38
#define KEY_SPACE  0x39
#define KEY_CAPS   0x3A
#define KEY_F1     0x3B
#define KEY_F2     0x3C
#define KEY_F3     0x3D
#define KEY_F4     0x3E
#define KEY_F5     0x3F
#define KEY_F6     0x40
#define KEY_F7     0x41
#define KEY_F8     0x42
#define KEY_F9     0x43
#define KEY_F10    0x44
#define KEY_NUMLOCK  0x45
#define KEY_SCROLLLOCK  0x46
#define KEY_HOME   0x47
#define KEY_UP     0x48
#define KEY_PAGEUP 0x49
#define KEY_KP_MINUS  0x4A
#define KEY_LEFT   0x4B
#define KEY_KP_5   0x4C
#define KEY_RIGHT  0x4D
#define KEY_KP_PLUS  0x4E
#define KEY_END    0x4F
#define KEY_DOWN   0x50
#define KEY_PAGEDOWN  0x51
#define KEY_INSERT 0x52
#define KEY_DELETE 0x53
#define KEY_F11    0x57
#define KEY_F12    0x58

// Special keys (extended with 0xE0 prefix)
#define KEY_WIN1   0x5B  // Left Windows
#define KEY_WIN2   0x5C  // Right Windows
#define KEY_MENU   0x5D  // Menu key
#define KEY_CTRL_R 0xE01D
#define KEY_ALT_R  0xE038
#define KEY_ENTER_KP  0xE01C
#define KEY_SLASH_KP  0xE035
#define KEY_PRINTSCREEN  0xE037
#define KEY_PAUSE   0xE045
#define KEY_HOME_E  0xE047
#define KEY_UP_E    0xE048
#define KEY_PAGEUP_E  0xE049
#define KEY_LEFT_E  0xE04B
#define KEY_RIGHT_E 0xE04D
#define KEY_END_E   0xE04F
#define KEY_DOWN_E  0xE050
#define KEY_PAGEDOWN_E  0xE051
#define KEY_INSERT_E  0xE052
#define KEY_DELETE_E  0xE053


int upper = false;


BYTE getKeyPress()
{
    BYTE scan = inb(0x60);
    BYTE isPress = !(scan & 0x80); 
    scan &= 0x7F; // Remove a bit
    if(isPress)
        return scan;
    else
        return 0;
}