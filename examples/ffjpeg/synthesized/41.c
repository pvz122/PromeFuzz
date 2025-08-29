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

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    // Create a dummy file to use as a stream
    const char *dummy_file = "./dummy_file";
    FILE *file = fopen(dummy_file, "wb+");
    if (!file) return 0;

    // Initialize a bitstream
    void *stream = bitstr_open((void *)dummy_file, "wb+", 0);
    if (!stream) {
        fclose(file);
        return 0;
    }

    // Fuzzing bitstr_putc
    for (size_t i = 0; i < Size; i++) {
        bitstr_putc(Data[i], stream);
    }

    // Fuzzing bitstr_putb
    for (size_t i = 0; i < Size; i++) {
        bitstr_putb(Data[i] % 2, stream); // Write a single bit
    }

    // Fuzzing bitstr_put_bits
    for (size_t i = 0; i < Size; i++) {
        bitstr_put_bits(stream, Data[i], 8); // Write 8 bits
    }

    // Fuzzing bitstr_flush
    bitstr_flush(stream, 0); // Flush with flag 0

    // Safely fuzzing bitstr_seek
    if (Size > 0) {
        long offset = rand() % Size;
        bitstr_seek(stream, offset, 0); // Seek to a random position
    }

    // Fuzzing bitstr_close
    bitstr_close(stream); // Close the stream
    fclose(file); // Close the dummy file

    return 0;
}