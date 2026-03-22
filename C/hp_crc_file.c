/* CRC calculation for HP1630A configuration files */

#include <stdio.h>
#include <stdlib.h>

unsigned int CRC_table[256];

unsigned int HP_CRC(unsigned char *buffer, int length, int seed);
void HP_CRC_Initialise(unsigned int poly);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <configfile>\n", argv[0]);
        return 1;
    }

    /* --- open file --- */
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        perror("Cannot open file");
        return 1;
    }

    /* --- read entire file --- */
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char *buf = malloc(filesize);
    if (!buf) {
        printf("Memory allocation failed\n");
        return 1;
    }

    fread(buf, 1, filesize, f);
    fclose(f);

    /* --- check header --- */
    if (buf[0] != 'R' || buf[1] != 'C') {
        printf("Error: file does not start with 'RC'\n");
        
    }

    /* length field (bytes 3–4), MSB first */
    unsigned int count = (buf[2] << 8) | buf[3];

    printf("Header length field: %u bytes follow\n", count);
    printf("Total file size:     %ld bytes\n", filesize);

    /* expected total = 4 header bytes + count */
    if (filesize != (long)(4 + count)) {
        printf("WARNING: file size does not match header length!\n");
    }

    /* --- CRC range --- */
    unsigned char *data = buf + 4;          /* start at byte 5 */
    int data_len = count - 2;               /* exclude CRC bytes */

    unsigned char crc_hi = buf[4 + data_len];
    unsigned char crc_lo = buf[4 + data_len + 1];

    unsigned int stored_crc = (crc_hi << 8) | crc_lo;

    /* --- compute CRC --- */
    HP_CRC_Initialise(0x8005);

    unsigned int calc_crc = HP_CRC(data, data_len, 0);

    printf("Stored CRC: %04X\n", stored_crc);
    printf("Calc   CRC: %04X\n", calc_crc);

    if (stored_crc == calc_crc)
        printf("CRC MATCHES\n");
    else
        printf("CRC MISMATCH\n");

    free(buf);
    return 0;
}

/* --- HP1630 CRC implementation --- */

unsigned int HP_CRC(unsigned char *buffer, int length, int seed)
{
    int x = 0;
    while (length > 0) {
        seed = (seed & 0xff00) ^ CRC_table[(seed ^ buffer[x++]) & 0xff];
        length--;
    }
    return seed;
}

void HP_CRC_Initialise(unsigned int poly)
{
    unsigned int crc, x, y;

    for (x = 0; x < 256; x++) {
        crc = x;
        for (y = 0; y < 16; y++) {
            crc <<= 1;
            if (crc & 0x10000)
                crc ^= poly;
            crc &= 0xffff;
        }
        CRC_table[x] = crc;
    }
}
