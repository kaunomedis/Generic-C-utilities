/* Convert RAW bitmap files from 24 bit to 16 bit LCD screens */
/* (c)2026 http://www.vabolis.lt */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Macro to pack 8-bit RGB into 16-bit RGB565
#define RGB888_TO_RGB565(r,g,b)            (uint16_t)((((r) >> 3) << 11) | (((g) >> 2) << 5) | ((b) >> 3))

#define ILI9341_COLOR(red, green, blue)   ((unsigned int)( (( red >> 3 ) << 11 ) | (( green >> 2 ) << 5  ) |  ( blue  >> 3 ))) 


int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s input.raw output.bin output.c\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "rb");
    if (!fin) {
        perror("Error opening input file");
        return 1;
    }

    FILE *fbin = fopen(argv[2], "wb");
    if (!fbin) {
        perror("Error opening output binary file");
        fclose(fin);
        return 1;
    }

    FILE *fc = fopen(argv[3], "w");
    if (!fc) {
        perror("Error opening output C file");
        fclose(fin);
        fclose(fbin);
        return 1;
    }

    fprintf(fc, "/* Auto-generated RGB565 image data. BIG ENDIAN */\n");
	fprintf(fc, "/* source filename: %s */\n\n",argv[1]);
    fprintf(fc, "#include <stdint.h>\n\n");
    fprintf(fc, "const unsigned char image_data[] = {\n");

    unsigned long count = 0;
    while (1) {
        unsigned char rgb[3];
        size_t read = fread(rgb, 1, 3, fin);
        
		
		if (read < 3) {
        if (read !=0) fprintf(stderr, "Unexpected EOF\n");
        break;
    }

        uint16_t pixel = RGB888_TO_RGB565(rgb[0], rgb[1], rgb[2]); 

        // Split into bytes (little endian: low byte first)
        unsigned char low = pixel & 0xFF;
        unsigned char high = (pixel >> 8) & 0xFF;

        // Write to binary file
        
        fwrite(&high, 1, 1, fbin);
		fwrite(&low, 1, 1, fbin);
        // Write to C file
        fprintf(fc, "0x%02X,0x%02X,", high, low);
        count += 2;
        if (count % 24 == 0) fprintf(fc, "\n");
    }

    fprintf(fc, "\n};\n");
    fprintf(fc, "const unsigned long image_data_size = %lu;\n", count);

    fclose(fin);
    fclose(fbin);
    fclose(fc);

    printf("Converted %lu bytes.\n", count);
    return 0;
}
