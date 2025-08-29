// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bitstr_open at bitstr.c:176:7 in bitstr.h
// bitstr_close at bitstr.c:185:5 in bitstr.h
// bitstr_putc at bitstr.c:209:5 in bitstr.h
// bitstr_putb at bitstr.c:273:5 in bitstr.h
// bitstr_get_bits at bitstr.c:299:5 in bitstr.h
// bitstr_put_bits at bitstr.c:309:5 in bitstr.h
// bitstr_flush at bitstr.c:321:5 in bitstr.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bitstr.h"

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a dummy bitstream
    char fnamebuf[256] = "./dummy_file";
    void *stream = bitstr_open(fnamebuf, "wb", 1024);
    if (!stream) return 0;

    // Fuzz bitstr_putc
    for (size_t i = 0; i < Size; i++) {
        bitstr_putc(Data[i], stream);
    }

    // Fuzz bitstr_putb
    for (size_t i = 0; i < Size; i++) {
        bitstr_putb(Data[i] & 1, stream);
    }

    // Fuzz bitstr_put_bits
    for (size_t i = 0; i < Size; i++) {
        bitstr_put_bits(stream, Data[i], (Data[i] % 8) + 1);
    }

    // Fuzz bitstr_flush
    bitstr_flush(stream, Size % 2);

    // Close the stream
    bitstr_close(stream);

    // Reopen the stream for reading
    stream = bitstr_open(fnamebuf, "rb", 1024);
    if (!stream) return 0;

    // Fuzz bitstr_get_bits
    for (size_t i = 0; i < Size; i++) {
        bitstr_get_bits(stream, (Data[i] % 8) + 1);
    }

    // Close the stream
    bitstr_close(stream);

    return 0;
}