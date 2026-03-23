/* program to scan and replace text to hex notation in uncompressed pdf file */
/* this util is used to debug some automated pdf from php libraries */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static void write_hex(FILE *out, int c) {
    static const char *hex = "0123456789ABCDEF";
    fputc(hex[(c >> 4) & 0xF], out);
    fputc(hex[c & 0xF], out);
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

        // Convert literal string only inside BT...ET
        if (in_text && c == '(') {

            fputc('<', out);  // begin hex string

            int depth = 1;
            while ((d = fgetc(in)) != EOF) {

                if (d == '\\') {
                    // escaped character
                    int e = fgetc(in);
                    if (e == EOF) break;
                    write_hex(out, e);
                    continue;
                }

                if (d == '(') depth++;
                if (d == ')') depth--;

                if (depth == 0)
                    break;

                write_hex(out, d);
            }

            fputc('>', out);  // end hex string
            continue;
        }

        // Default: copy byte
        fputc(c, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
