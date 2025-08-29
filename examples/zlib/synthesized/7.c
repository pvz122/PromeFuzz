// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gzputc at gzwrite.c:287:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
// gzputs at gzwrite.c:332:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    const char *filename = "./dummy_file";
    FILE *fp = fopen(filename, "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    gzFile file = gzopen(filename, "wb");
    if (!file) return 0;

    int c = Data[0];
    gzputc(file, c);

    const char *s = (const char *)(Data + 1);
    size_t s_len = Size - 1;
    if (s_len > 0) {
        char *str = malloc(s_len + 1);
        if (!str) {
            gzclose(file);
            return 0;
        }
        memcpy(str, s, s_len);
        str[s_len] = '\0';
        gzputs(file, str);
        free(str);
    }

    gzclose(file);
    return 0;
}