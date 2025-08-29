// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bitstr_open at bitstr.c:176:7 in bitstr.h
// bitstr_close at bitstr.c:185:5 in bitstr.h
// bitstr_putc at bitstr.c:209:5 in bitstr.h
// bitstr_seek at bitstr.c:221:5 in bitstr.h
// bitstr_putb at bitstr.c:273:5 in bitstr.h
// bitstr_put_bits at bitstr.c:309:5 in bitstr.h
// bitstr_flush at bitstr.c:321:5 in bitstr.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bitstr.h"

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    // Initialize a bitstream
    void *stream = bitstr_open(NULL, "wb", 1024); // Opening a stream with mode and buffer size

    if (stream == NULL) {
        return 0; // Stream initialization failed
    }

    // Fuzzing the bitstr_putc function
    for (size_t i = 0; i < Size; i++) {
        bitstr_putc(Data[i], stream);
    }

    // Fuzzing the bitstr_putb function
    for (size_t i = 0; i < Size; i++) {
        bitstr_putb(Data[i] % 2, stream); // Writing a single bit
    }

    // Fuzzing the bitstr_put_bits function
    if (Size >= 4) {
        int bits = *(int*)Data; // Getting an integer from data
        bitstr_put_bits(stream, bits, 8); // Writing 8 bits
    }

    // Fuzzing the bitstr_seek function
    bitstr_seek(stream, rand() % Size, SEEK_SET);
    bitstr_seek(stream, rand() % Size, SEEK_CUR);
    bitstr_seek(stream, rand() % Size, SEEK_END);

    // Fuzzing the bitstr_flush function
    bitstr_flush(stream, 0);

    // Fuzzing the bitstr_close function
    bitstr_close(stream);

    return 0;
}