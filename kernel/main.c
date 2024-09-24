#include "main.h"
#include "framebuffer.h"


// void set_video_mode_13h() {
//     // Write to the Miscellaneous Output Register (port 0x03C2)
//     outb(0x03C2, 0x63);

//     // Set the mode to 13h (320x200, 256 colors) by writing to the CRT Controller (CRTC) register (port 0x03D4)
//     outb(0x03D4, 0x13);

//     // Write to the VGA Attribute Controller (port 0x03C0) to set the mode
//     outb(0x03C0, 0x13);

//     // You may also need to reset the VGA Sequencer and other registers if required by your system.
//     // Example:
//     // outb(0x03C4, 0x04);  // Reset Sequencer
//     // outb(0x03C4, 0x03);  // Sequencer Settings

//     // Optionally clear the screen
//     // outb(0x03C8, 0x00);  // Reset color palette index
//     // outb(0x03C9, 0x00);  // Set color to black
// }

// void plot_pixel(int x, int y, uint8_t color) {
//     // Calculate the memory offset for (x, y)
//     uint8_t *video_memory = (uint8_t*)0xA0000;
//     video_memory[y * 320 + x] = color;
// }

void kmain() {
    // set_video_mode_13h();  // Set video mode to 13h
    char text[] = "4re5 os - V1.0";
    fb_write(text, sizeof(text));

    // __asm__ (
    //     "movb $0x0E, %%ah\n\t"  // Move 0x0E (teletype output function) into AH
    //     "movb $'!', %%al\n\t"   // Move the character '!' into AL
    //     "int $0x10\n\t"         // Call BIOS interrupt 0x10 (video services)
    //     :
    //     : 
    //     : "ah", "al"            // Marking AH and AL as clobbered
    // );
    // Keep the screen active (in a real OS, you would have more control)
    // while (1);
}