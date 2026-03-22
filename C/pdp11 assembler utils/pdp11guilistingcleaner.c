/* removes additional alternative listings from output, cleans up for processing and assembler */
/* only for PDP11 disassembler output */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "PDP11GUI dis listing cleaner. Usage: %s <input.txt> <output.txt>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (!fin) {
        perror("Error opening input file");
        return 1;
    }

    FILE *fout = fopen(argv[2], "w");
    if (!fout) {
        perror("Error opening output file");
        fclose(fin);
        return 1;
    }

    char buffer[4096];

    while (fgets(buffer, sizeof(buffer), fin)) {
        int i = 0;
        int space_count = 0;

        /* Count leading spaces and detect TAB */
        while (buffer[i] == ' ' || buffer[i] == '\t') {
            if (buffer[i] == '\t') {
                space_count = 3;  /* Force skip */
                break;
            }
            space_count++;
            i++;
        }

        /* Skip if more than 2 spaces or any TAB */
        if (space_count > 2)
            continue;

        fputs(buffer, fout);
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
