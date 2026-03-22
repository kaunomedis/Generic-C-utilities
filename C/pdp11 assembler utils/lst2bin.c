/* tries to convert disassembler listing to binary */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MEM 65536

static unsigned char mem[MAX_MEM];
static int used[MAX_MEM];

static int is_octal_n(const char *s, int n) {
    for (int i = 0; i < n; i++) {
        if (!s[i]) return 0;
        if (s[i] < '0' || s[i] > '7') return 0;
    }
    return 1;
}

static int parse_octal_n(const char *s, int n) {
    int v = 0;
    for (int i = 0; i < n; i++) {
        v = (v << 3) | (s[i] - '0');
    }
    return v;
}

int main(int argc, char **argv) {
fprintf(stderr, "PDP11 macro assemble listing to binary converter.\n");
    if (argc != 3) {
        fprintf(stderr, "usage: %s input.lst output.bin\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("input");
        return 1;
    }

    char line[1024];

    while (fgets(line, sizeof(line), in)) {
        char *p = line;

        /* skip leading spaces */
        while (*p == ' ' || *p == '\t') p++;

        /* skip line number (digits) */
        while (*p >= '0' && *p <= '9') p++;

        /* skip spaces after line number */
        while (*p == ' ' || *p == '\t') p++;

        /* need 6-digit octal address */
        if (!is_octal_n(p, 6))
            continue;

        int addr = parse_octal_n(p, 6);
        if (addr < 0 || addr >= MAX_MEM)
            continue;

        p += 6;

        /* skip spaces before data */
        while (*p == ' ' || *p == '\t') p++;

        if (!*p)
            continue;

        /* detect mode: word (6-digit) or byte (3-digit) */
        int mode = 0; /* 1 = word, 2 = byte */
        if (is_octal_n(p, 6))
            mode = 1;
        else if (is_octal_n(p, 3))
            mode = 2;
        else
            continue;

        while (*p) {
            while (*p == ' ' || *p == '\t') p++;
            if (!*p) break;

            if (mode == 1) {
                if (!is_octal_n(p, 6)) break;
                int w = parse_octal_n(p, 6);
                if (addr + 1 < MAX_MEM) {
                    mem[addr]     = (unsigned char)(w & 0xFF);
                    mem[addr + 1] = (unsigned char)((w >> 8) & 0xFF);
                    used[addr] = used[addr + 1] = 1;
                }
                addr += 2;
                p += 6;
            } else { /* mode == 2, bytes */
                if (!is_octal_n(p, 3)) break;
                int b = parse_octal_n(p, 3);
                if (addr < MAX_MEM) {
                    mem[addr] = (unsigned char)(b & 0xFF);
                    used[addr] = 1;
                }
                addr += 1;
                p += 3;
            }
        }
    }

    fclose(in);

    int maxaddr = -1;
    for (int i = 0; i < MAX_MEM; i++)
        if (used[i]) maxaddr = i;

    FILE *out = fopen(argv[2], "wb");
    if (!out) {
        perror("output");
        return 1;
    }

    if (maxaddr >= 0)
        fwrite(mem, 1, maxaddr + 1, out);

    fclose(out);
    return 0;
}
