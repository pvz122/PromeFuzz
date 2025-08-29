// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gzseek64 at gzlib.c:342:19 in zlib.h
// gzoffset at gzlib.c:467:17 in zlib.h
// gztell at gzlib.c:438:17 in zlib.h
// gztell64 at gzlib.c:423:19 in zlib.h
// gzseek at gzlib.c:415:17 in zlib.h
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

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
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

    int whence = (Data[0] % 2) ? SEEK_SET : SEEK_CUR;
    z_off64_t offset = (z_off64_t)Data[0];

    gzseek64(gz, offset, whence);
    gzoffset(gz);
    gztell(gz);
    gztell64(gz);
    gzseek(gz, (z_off_t)offset, whence);
    gzoffset64(gz);

    gzclose(gz);
    remove("./dummy_file");

    return 0;
}