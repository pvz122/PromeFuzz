// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gzseek64 at gzlib.c:342:19 in zlib.h
// gzoffset at gzlib.c:467:17 in zlib.h
// gztell at gzlib.c:438:17 in zlib.h
// gztell64 at gzlib.c:423:19 in zlib.h
// gzoffset64 at gzlib.c:446:19 in zlib.h
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

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_off64_t) + sizeof(int)) {
        return 0;
    }

    z_off64_t offset = *((z_off64_t *)Data);
    int whence = *((int *)(Data + sizeof(z_off64_t)));

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        return 0;
    }
    fwrite(Data + sizeof(z_off64_t) + sizeof(int), 1, Size - sizeof(z_off64_t) - sizeof(int), file);
    fclose(file);

    gzFile gzfile = gzopen("./dummy_file", "rb");
    if (!gzfile) {
        return 0;
    }

    z_off64_t seek_result = gzseek64(gzfile, offset, whence);
    if (seek_result != -1) {
        z_off_t offset_result = gzoffset(gzfile);
        z_off_t tell_result = gztell(gzfile);
        z_off64_t tell64_result = gztell64(gzfile);
        z_off64_t offset64_result = gzoffset64(gzfile);
    }

    gzclose(gzfile);
    return 0;
}