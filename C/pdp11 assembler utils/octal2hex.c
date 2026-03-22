/* converts OCTAL notation to HEX notation. To same my brain from melting */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_MAX 4096

/* Convert substring [start, end) containing an octal number to 0xHHHH */
static void append_octal_as_hex16(char *out, size_t *out_pos,
                                  const char *start, const char *end)
{
    char buf[16];
    int len = (int)(end - start);

    if (len <= 0 || len >= (int)sizeof(buf)) {
        while (start < end && *out_pos < LINE_MAX - 1)
            out[(*out_pos)++] = *start++;
        return;
    }

    memcpy(buf, start, len);
    buf[len] = '\0';

    char *endptr = NULL;
    long val = strtol(buf, &endptr, 8);

    if (*endptr != '\0' || val < 0 || val > 0xFFFF) {
        while (start < end && *out_pos < LINE_MAX - 1)
            out[(*out_pos)++] = *start++;
        return;
    }

    *out_pos += snprintf(out + *out_pos, LINE_MAX - *out_pos,
                         "0x%04X", (unsigned int)val);
}

static int is_register_name(const char *s, size_t len)
{
    /* Matches r0–r7 exactly */
    return (len == 2 &&
            s[0] == 'r' &&
            s[1] >= '0' && s[1] <= '7');
}

static void process_file(FILE *in, FILE *outf)
{
    char line[LINE_MAX];

    while (fgets(line, sizeof(line), in)) {
        char out[LINE_MAX * 2];
        size_t out_pos = 0;

        size_t i = 0;
        size_t len = strlen(line);

        while (i < len) {

            /* T1 spacing: runs of >=2 spaces ? TAB */
            if (line[i] == ' ') {
                size_t j = i;
                while (j < len && line[j] == ' ')
                    j++;

                size_t count = j - i;

                if (count == 1)
                    out[out_pos++] = ' ';
                else
                    out[out_pos++] = '\t';

                i = j;
                continue;
            }

            /* Detect octal token: 1–6 digits [0–7] */
            if (line[i] >= '0' && line[i] <= '7') {
                size_t start = i;
                size_t j = i;

                while (j < len && line[j] >= '0' && line[j] <= '7')
                    j++;

                size_t digits = j - start;

                /* Skip single-digit numbers (register names, etc.) */
                if (digits == 1) {
                    out[out_pos++] = line[i++];
                    continue;
                }

                /* Check boundaries: must be word-bounded */
                int left_ok = (start == 0) ||
                              !isdigit((unsigned char)line[start - 1]);
                int right_ok = (j >= len) ||
                               !isdigit((unsigned char)line[j]);

                if (digits >= 2 && digits <= 6 && left_ok && right_ok) {
                    append_octal_as_hex16(out, &out_pos,
                                          &line[start], &line[j]);
                    i = j;
                    continue;
                }

                /* Not a valid octal token ? copy one char */
                out[out_pos++] = line[i++];
                continue;
            }

            /* Skip register names r0–r7 explicitly */
            if (line[i] == 'r' && i + 1 < len &&
                line[i+1] >= '0' && line[i+1] <= '7')
            {
                out[out_pos++] = line[i++];
                out[out_pos++] = line[i++];
                continue;
            }

            /* Default: copy character */
            out[out_pos++] = line[i++];
        }

        out[out_pos] = '\0';
        fputs(out, outf);
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr,
            "Usage: %s <inputfile> <outputfile>\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Input file");
        return 1;
    }

    FILE *outf = fopen(argv[2], "w");
    if (!outf) {
        perror("Output file");
        fclose(in);
        return 1;
    }

    process_file(in, outf);

    fclose(in);
    fclose(outf);
    return 0;
}
