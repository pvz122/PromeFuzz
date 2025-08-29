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

#define ZLIB_CONST
#include <zlib.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Write the input data to a dummy file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file with gzopen
    gzFile gzfile = gzopen("./dummy_file", "rb");
    if (!gzfile) {
        remove("./dummy_file");
        return 0;
    }

    // Fuzz gzoffset
    z_off_t offset = gzoffset(gzfile);
    (void)offset;

    // Fuzz gztell
    z_off_t tell = gztell(gzfile);
    (void)tell;

    // Fuzz gzseek
    int whence = Data[0] % 2 ? SEEK_SET : SEEK_CUR;
    z_off_t seek_offset = gzseek(gzfile, (z_off_t)Data[0], whence);
    (void)seek_offset;

    // Clean up
    gzclose(gzfile);
    remove("./dummy_file");

    return 0;
}