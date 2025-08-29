// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bitstr_get_bits at bitstr.c:299:5 in bitstr.h
// huffman_decode_done at huffman.c:328:6 in huffman.h
// huffman_decode_run at huffman.c:333:6 in huffman.h
// huffman_decode_step at huffman.c:357:5 in huffman.h
// huffman_encode_step at huffman.c:283:6 in huffman.h
// huffman_decode_init at huffman.c:300:6 in huffman.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "bitstr.h"

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(HUFCODEC)) return 0;

    // Initialize the codec context
    HUFCODEC *phc = (HUFCODEC *)malloc(sizeof(HUFCODEC));
    if (!phc) return 0;

    // Initialize the bitstream
    void *stream = malloc(Size);
    if (!stream) {
        free(phc);
        return 0;
    }
    memcpy(stream, Data, Size);

    // Initialize the Huffman decoder
    huffman_decode_init(phc);

    // Fuzzing bitstr_get_bits
    for (int i = 1; i <= 32; i++) {
        bitstr_get_bits(stream, i);
    }

    // Fuzzing huffman_decode_run
    huffman_decode_run(phc);

    // Fuzzing huffman_decode_step
    for (int i = 0; i < 10; i++) {
        huffman_decode_step(phc);
    }

    // Fuzzing huffman_encode_step with random symbol
    for (int i = 0; i < 10; i++) {
        huffman_encode_step(phc, rand() % 256);
    }

    // Cleanup
    huffman_decode_done(phc);
    free(stream);
    free(phc);

    return 0;
}