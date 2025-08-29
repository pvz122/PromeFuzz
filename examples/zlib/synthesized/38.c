// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// gzopen at gzlib.c:263:16 in zlib.h
// gzsetparams at gzwrite.c:557:13 in zlib.h
// gzwrite at gzwrite.c:237:13 in zlib.h
// gzputs at gzwrite.c:332:13 in zlib.h
// gzprintf at gzwrite.c:430:15 in zlib.h
// gzflush at gzwrite.c:528:13 in zlib.h
// gzclose_w at gzwrite.c:595:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    write_dummy_file(data, size);

    gzFile file = gzopen("./dummy_file", "wb");
    if (!file) return 0;

    int level = data[0] % 10;
    int strategy = data[0] % 4;
    int flush = data[0] % 3;

    gzsetparams(file, level, strategy);
    gzwrite(file, data, size);
    gzputs(file, "test string");
    gzprintf(file, "test format %d", level);
    gzflush(file, flush);
    gzclose_w(file);

    return 0;
}