// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gzgetc_ at gzread.c:434:13 in zlib.h
// gzseek at gzlib.c:415:17 in zlib.h
// gzdirect at gzread.c:560:13 in zlib.h
// gzrewind at gzlib.c:321:13 in zlib.h
// gzeof at gzlib.c:475:13 in zlib.h
// gzclose at gzclose.c:11:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static gzFile create_dummy_gzfile(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return NULL;
    fwrite(data, 1, size, file);
    fclose(file);

    return gzopen("./dummy_file", "rb");
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    gzFile file = create_dummy_gzfile(Data, Size);
    if (!file) return 0;

    // Test gzgetc_
    gzgetc_(file);

    // Test gzseek
    gzseek(file, Size / 2, SEEK_SET);

    // Test gzdirect
    gzdirect(file);

    // Test gzrewind
    gzrewind(file);

    // Test gzeof
    gzeof(file);

    gzclose(file);
    return 0;
}