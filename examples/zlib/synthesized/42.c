// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gzoffset at gzlib.c:467:17 in zlib.h
// gztell at gzlib.c:438:17 in zlib.h
// gzseek at gzlib.c:415:17 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ZLIB_WINAPI
#define Z_LARGE64

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    gzFile gz = gzopen("./dummy_file", "rb");
    if (!gz) {
        remove("./dummy_file");
        return 0;
    }

    z_off_t offset = gzoffset(gz);
    z_off_t tell = gztell(gz);
    z_off_t seek = gzseek(gz, Size / 2, SEEK_SET);

    gzclose(gz);
    remove("./dummy_file");

    return 0;
}