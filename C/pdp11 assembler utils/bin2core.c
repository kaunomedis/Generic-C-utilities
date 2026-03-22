/* converts binary to PDP11 ODT load text stream */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    const char *infile;
    const char *outfile;
    unsigned long start = 0;
    FILE *fi, *fo;
    long size;
    unsigned char *buf;
    int i;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s input.bin [start_hex] output.txt\n", argv[0]);
        return 1;
    }

    infile = argv[1];

    if (argc == 3) {
        // no start address, only output file
        outfile = argv[2];
    } else {
        // start address + output file
        start = strtoul(argv[2], NULL, 16);
        outfile = argv[3];
    }

    fi = fopen(infile, "rb");
    if (!fi) {
        perror(infile);
        return 1;
    }

    fo = fopen(outfile, "w");
    if (!fo) {
        perror(outfile);
        fclose(fi);
        return 1;
    }

    fseek(fi, 0, SEEK_END);
    size = ftell(fi);
    fseek(fi, 0, SEEK_SET);

    buf = malloc(size);
    if (!buf) {
        fprintf(stderr, "Out of memory\n");
        fclose(fi);
        fclose(fo);
        return 1;
    }

    if (fread(buf, 1, size, fi) != size) {
        fprintf(stderr, "Read error\n");
        free(buf);
        fclose(fi);
        fclose(fo);
        return 1;
    }

    fclose(fi);

    // Write in disas11 core format
    fprintf(fo, "%lX %lX", start, (unsigned long)size);
    for (i = 0; i < size; i++)
        fprintf(fo, " %02X", buf[i]);
    fprintf(fo, "\n");

    free(buf);
    fclose(fo);

    return 0;
}
