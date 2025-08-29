// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bitstr_open at bitstr.c:176:7 in bitstr.h
// bitstr_close at bitstr.c:185:5 in bitstr.h
// bitstr_getc at bitstr.c:197:5 in bitstr.h
// bitstr_seek at bitstr.c:221:5 in bitstr.h
// bitstr_getb at bitstr.c:245:5 in bitstr.h
// bitstr_get_bits at bitstr.c:299:5 in bitstr.h
// bitstr_put_bits at bitstr.c:309:5 in bitstr.h
// bitstr_flush at bitstr.c:321:5 in bitstr.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitstr.h"

#define DUMMY_FILE "./dummy_file"
#define BUFFER_SIZE 1024

void setup_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Setup dummy file with input data
    setup_dummy_file(Data, Size);

    // Initialize bitstream
    void *stream = bitstr_open(DUMMY_FILE, "rb", BUFFER_SIZE);
    if (!stream) return 0;

    // Fuzzing bitstr_get_bits
    for (int i = 1; i <= 32; i++) {
        bitstr_get_bits(stream, i);
    }

    // Fuzzing bitstr_getc
    bitstr_getc(stream);

    // Fuzzing bitstr_flush
    bitstr_flush(stream, 0);
    bitstr_flush(stream, 1);

    // Fuzzing bitstr_getb
    bitstr_getb(stream);

    // Fuzzing bitstr_put_bits
    for (int i = 1; i <= 32; i++) {
        bitstr_put_bits(stream, rand() % (1 << i), i);
    }

    // Fuzzing bitstr_seek
    bitstr_seek(stream, 0, SEEK_SET);
    bitstr_seek(stream, 0, SEEK_CUR);
    bitstr_seek(stream, 0, SEEK_END);

    // Cleanup
    bitstr_close(stream);
    remove(DUMMY_FILE);

    return 0;
}