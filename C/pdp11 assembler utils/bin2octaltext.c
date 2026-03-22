/* converts binary file to octal notation text file */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input.bin output.txt base_octal\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        perror("Input file");
        return 1;
    }

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        perror("Output file");
        fclose(in);
        return 1;
    }

    // Parse base address (octal)
    unsigned int base = strtol(argv[3], NULL, 8);

    unsigned int offset = 0;
    int b1, b2;

    while (1) {
        b1 = fgetc(in);
        if (b1 == EOF)
            break;

        b2 = fgetc(in);
        if (b2 == EOF)
            b2 = 0;   // pad odd byte count

        // PDP-11 little-endian word
        unsigned int word = (b2 << 8) | b1;

        // Output: (base + offset) / word
        fprintf(out, "%o/%o\n", base + offset, word);

        offset += 2;
    }

    fclose(in);
    fclose(out);
	fprintf(stderr,"Done\r\n");
    return 0;
}
