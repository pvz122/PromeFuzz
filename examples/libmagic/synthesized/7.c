// This fuzz driver is generated for library libmagic, aiming to fuzz the following functions:
// magic_open at magic.c:267:1 in magic.h
// magic_compile at magic.c:340:1 in magic.h
// magic_error at magic.c:567:1 in magic.h
// magic_open at magic.c:267:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
// magic_list at magic.c:356:1 in magic.h
// magic_error at magic.c:567:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
// magic_close at magic.c:306:1 in magic.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <magic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return;
    fwrite(data, 1, size, file);
    fclose(file);
}

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    write_dummy_file(data, size);

    magic_t magic = magic_open(MAGIC_NONE);
    if (!magic) return 0;

    magic_compile(magic, "./dummy_file");
    magic_error(magic);

    magic_t magic2 = magic_open(MAGIC_NONE);
    if (!magic2) {
        magic_close(magic);
        return 0;
    }

    magic_list(magic2, "./dummy_file");
    magic_error(magic2);

    magic_close(magic);
    magic_close(magic2);

    return 0;
}