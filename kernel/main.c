// #define VGA_WIDTH 80
// #define VGA_HEIGHT 25
// #define VGA_ADDRESS 0xB8000

// // VGA color attributes
// #define WHITE_ON_BLACK 0x0F
// #define BLUE_ON_BLACK 0x01
// #define GREEN_ON_BLACK 0x02
// #define RED_ON_BLACK 0x04
// #define CYAN_ON_BLACK 0x03
// #define MAGENTA_ON_BLACK 0x05
// #define YELLOW_ON_BLACK 0x0E

// volatile unsigned short* vga_buffer = (unsigned short*)VGA_ADDRESS;



// // Function to print a single character with color
// void print_char(int row, int col, unsigned char character, unsigned attribute) {
//     int position = row * VGA_WIDTH + col;
//     // Write the character and its attribute to VGA memory
//     vga_buffer[position] = (attribute << 8) | character;
// }

// // Function to print a string with multiple colors, starting at (row, col)
// void print_string(const char* str, int row, int col, unsigned char attribute) {
//     int i = 0;
//     while (str[i] != '\0') {
//         print_char(row, col + i, str[i], attribute);
//         i++;
//     }
// }

// int strlen(const char* str) {
//     int length = 0;
//     while (str[length] != '\0') {
//         length++;
//     }
//     return length;
// }

// void clearScr() {
//     for (int row = 0; row < VGA_HEIGHT; row++) {
//         for (int col = 0; col < VGA_WIDTH; col++) {
//             print_char(row, col, ' ', WHITE_ON_BLACK);
//         }
//     }
// }

// void draw_window(int x, int y, int width, int height, const char *title) {
//     // Top-left corner
//     print_char(y, x, 201, WHITE_ON_BLACK); // ╔ (Code Page 437: 201)
    
//     // Top-right corner
//     print_char(y, x + width - 1, 187, WHITE_ON_BLACK); // ╗ (Code Page 437: 187)
    
//     // Bottom-left corner
//     print_char(y + height - 1, x, 200, WHITE_ON_BLACK); // ╚ (Code Page 437: 200)
    
//     // Bottom-right corner
//     print_char(y + height - 1, x + width - 1, 188, WHITE_ON_BLACK); // ╝ (Code Page 437: 188)
    
//     // Top and bottom borders
//     for (int i = 1; i < width - 1; i++) {
//         print_char(y, x + i, 205, WHITE_ON_BLACK); // ═ (Code Page 437: 205)
//         print_char(y + height - 1, x + i, 205, WHITE_ON_BLACK); // ═
//     }
    
//     // Left and right borders
//     for (int i = 1; i < height - 1; i++) {
//         print_char(y + i, x, 186, WHITE_ON_BLACK); // ║ (Code Page 437: 186)
//         print_char(y + i, x + width - 1, 186, WHITE_ON_BLACK); // ║
//     }
    
//     // Print the window title on the left side of the top border
//     for (int i = 0; title[i] != '\0'; i++) {
//         if (x + 1 + i >= x + width - 5) break; // Avoid title overlapping with the [x]
//         print_char(y, x + 1 + i, title[i], WHITE_ON_BLACK);
//     }
    
//     // Add the [x] button on the right side of the top border
//     const char *close_button = "[x]";
//     for (int i = 0; close_button[i] != '\0'; i++) {
//         print_char(y, x + width - 4 + i, close_button[i], WHITE_ON_BLACK);
//     }
// }

// unsigned char scancode_to_ascii[128] = {
//     0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
//     '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
//     'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
//     'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0,
//     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
// };
// char get_keypress() {
//     unsigned char scancode;
//     char key = 0;

//     // Wait until a key is pressed
//     while (1) {
//         asm volatile("inb $0x64, %0" : "=a"(scancode)); // Read status
//         if (scancode & 1) {                            // Data ready?
//             asm volatile("inb $0x60, %0" : "=a"(scancode)); // Read scancode
//             if (scancode < 128) {                          // Ignore release codes
//                 key = scancode_to_ascii[scancode];         // Convert to ASCII
//                 break;
//             }
//         }
//     }

//     return key;
// }

void kmain() {
    // Kernel main function
    const char *msg = "Hello from the kernel!";
    char *video_memory = (char *)0xB8000;

    for (int i = 0; msg[i] != '\0'; ++i) {
        video_memory[i * 2] = msg[i];      // Character
        video_memory[i * 2 + 1] = 0x07;   // Attribute (white on black)
    }

    while (1) {
        // Halt CPU
        asm volatile("hlt");
    }
}
// void kmain() {
    // asm volatile (
    //     "movb $0x0E, %%ah\n\t"
    //     "movb $'L', %%al\n\t"
    //     "int $0x10\n\t"
    //     :
    //     :
    //     : "ah", "al"
    // );
    // print_char(0, 0, 'i', BLUE_ON_BLACK);
    // clearScr();

    // draw_window(10, 10, 30, 20, "Test");

    // print_string("Press a key: ", 0, 0, WHITE_ON_BLACK);

    // Wait for keypress and display the character
    // while (1) {
        // char key = get_keypress();
        // if (key) {
        //     print_char(1, 0, key, WHITE_ON_BLACK);
        // }
    // }
    
    
    // Print "Hello World" at the top left of the screen without spaces
    // print_string("Hello World█", 0, 0);

    // Infinite loop to keep the kernel running
    // while (1) {}
//     return;
// }
