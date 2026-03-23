/* this util is used to scan uncompressed pdf file for text blocks and replace hex notation to ASC */
/* this program is used to debug some automated pdf creation libraries */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int hexval(int c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
}

static void write_literal_escaped(FILE *out, int c) {
    if (c == '(' || c == ')' || c == '\\')
        fputc('\\', out);
    fputc(c, out);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.pdf output.pdf\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        perror("Input open failed");
        return 1;
    }

    FILE *out = fopen(argv[2], "wb");
    if (!out) {
        perror("Output open failed");
        fclose(in);
        return 1;
    }

    int c, d;
    int in_text = 0;
    char token[3] = {0};
    int tpos = 0;

    while ((c = fgetc(in)) != EOF) {

        // Track BT / ET tokens
        if (!isspace(c)) {
            if (tpos < 2) token[tpos++] = (char)c;
        } else {
            token[0] = token[1] = 0;
            tpos = 0;
        }

        if (tpos == 2 && token[0] == 'B' && token[1] == 'T')
            in_text = 1;

        if (tpos == 2 && token[0] == 'E' && token[1] == 'T')
            in_text = 0;

        // Convert <HEX> only inside BT...ET
        if (in_text && c == '<') {
            char hexbuf[8192];
            int hlen = 0;

            while ((d = fgetc(in)) != EOF && d != '>') {
                if (!isspace(d) && hlen < (int)sizeof(hexbuf) - 1)
                    hexbuf[hlen++] = (char)d;
            }
            hexbuf[hlen] = '\0';

            // Write literal string
            fputc('(', out);

            if (hlen % 2 != 0) hlen--; // odd hex count ? drop last nibble

            for (int i = 0; i < hlen; i += 2) {
                int hi = hexval(hexbuf[i]);
                int lo = hexval(hexbuf[i + 1]);
                if (hi < 0 || lo < 0) break;
                unsigned char ch = (unsigned char)((hi << 4) | lo);
                write_literal_escaped(out, ch);
            }

            fputc(')', out);
            continue;
        }

        // Default: copy byte
        fputc(c, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
