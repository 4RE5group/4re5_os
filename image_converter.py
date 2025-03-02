from PIL import Image
import numpy as np

# Define the color mapping based on your kernel's color codes
COLOR_MAP = {
    (0, 0, 0): 0x00,       # Black
    (0, 0, 255): 0x01,     # Blue
    (0, 255, 0): 0x02,     # Green
    (0, 255, 255): 0x03,   # Cyan
    (255, 0, 0): 0x04,     # Red
    (255, 0, 255): 0x05,   # Magenta
    (255, 128, 0): 0x06,   # Orange
    (128, 128, 128): 0x07, # Grey
    (64, 64, 64): 0x08,    # Dark Grey
    (128, 0, 128): 0x09,   # Purple
    (0, 255, 128): 0x0A,   # Lime
    (64, 128, 64): 0x0B,   # Dark Gray-Green
    (255, 64, 64): 0x0C,   # Light Red
    (255, 192, 203): 0x0D, # Pink
    (255, 255, 0): 0x0E,   # Yellow
    (255, 255, 255): 0x0F  # White
}

# Convert dictionary keys to numpy array for fast distance calculation
COLOR_KEYS = np.array(list(COLOR_MAP.keys()))  # Array of RGB values
COLOR_VALUES = list(COLOR_MAP.values())        # Corresponding hex values

def find_nearest_color(rgb):
    """Finds the nearest defined color using Euclidean distance."""
    distances = np.sqrt(np.sum((COLOR_KEYS - rgb) ** 2, axis=1))
    return COLOR_VALUES[np.argmin(distances)]

def convert_image_to_c_header(input_file, output_file, var_name="icon"):
    img = Image.open(input_file).convert("RGB")  # Convert to RGB mode
    width, height = img.size
    pixels = img.load()

    header_guard = f"_{var_name.upper()}_H_"
    
    with open(output_file, "w") as f:
        # Write header guard
        f.write(f"#ifndef {header_guard}\n#define {header_guard}\n\n")
        f.write("#include <stdint.h>\n\n")
        
        # Define width and height
        f.write(f"#define {var_name.upper()}_WIDTH {width}\n")
        f.write(f"#define {var_name.upper()}_HEIGHT {height}\n\n")

        # Define pixel array
        f.write(f"static const uint8_t {var_name}[{width * height}] = {{\n    ")

        # Write pixel data
        pixel_data = []
        for y in range(height):
            row_data = []
            for x in range(width):
                color = pixels[x, y]
                color_code = COLOR_MAP.get(color, find_nearest_color(color))
                row_data.append(f"0x{color_code:02X}")
            pixel_data.append(", ".join(row_data))
        
        f.write(",\n    ".join(pixel_data))
        f.write("\n};\n\n")

        # End header guard
        f.write(f"#endif // {header_guard}\n")

    print(f"Generated C header file: {output_file}")


import os

output_dir = "./kernel/include/images/"
input_dir = "./images/"
for input_file in os.listdir(input_dir):
    if input_file.endswith(".png"):
        convert_image_to_c_header(input_dir+input_file, output_dir+input_file.replace(".png", ".h"), input_file.replace(".png", ""))
