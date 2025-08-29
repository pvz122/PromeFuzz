// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bitstr_close at bitstr.c:185:5 in bitstr.h
// bitstr_getc at bitstr.c:197:5 in bitstr.h
// bitstr_getb at bitstr.c:245:5 in bitstr.h
// bitstr_get_bits at bitstr.c:299:5 in bitstr.h
// bitstr_put_bits at bitstr.c:309:5 in bitstr.h
// bitstr_flush at bitstr.c:321:5 in bitstr.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bitstr.h"

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a bitstream
    void *stream = malloc(1024); // Allocate memory for the bitstream
    if (!stream) return 0;

    // Prepare the bitstream with the input data
    memcpy(stream, Data, Size < 1024 ? Size : 1024); // Copy data to the stream

    // Fuzzing various functions
    for (int i = 1; i <= 8; i++) {
        bitstr_put_bits(stream, Data[i % Size], i);
    }

    for (int i = 1; i <= 8; i++) {
        bitstr_get_bits(stream, i);
    }

    for (int i = 0; i < 8; i++) {
        bitstr_getc(stream);
    }

    for (int i = 0; i < 8; i++) {
        bitstr_getb(stream);
    }

    bitstr_flush(stream, 0);
    bitstr_close(stream);
    free(stream);

    return 0;
}