void set_red_pixel(int x, int y) {
    unsigned char *video_memory = (unsigned char *)0xA0000; // VESA framebuffer base address
    int offset = (y * 640) + x; // Offset to the pixel at (x, y)
    video_memory[offset] = 0x04; // Red color index (assuming 0x04 is red)
}

void main(void)
{
    for (int y=0; y<100; y++) {
        for (int x=0; x<100; x++) {
            set_red_pixel(x, y);  // Set pixel at (100, 100)
        }
        
       
    }
    return;
}

