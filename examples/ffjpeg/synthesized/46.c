// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// huffman_decode_done at huffman.c:328:6 in huffman.h
// huffman_decode_run at huffman.c:333:6 in huffman.h
// huffman_decode_step at huffman.c:357:5 in huffman.h
// huffman_encode_init at huffman.c:243:6 in huffman.h
// huffman_encode_run at huffman.c:258:6 in huffman.h
// huffman_decode_init at huffman.c:300:6 in huffman.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(HUFCODEC)) {
        return 0;
    }

    HUFCODEC hc;
    memcpy(&hc, Data, sizeof(HUFCODEC));

    // Initialize Huffman encoding
    huffman_encode_init(&hc, Size % 2);

    // Encode a run
    huffman_encode_run(&hc);

    // Initialize Huffman decoding
    huffman_decode_init(&hc);

    // Decode a single step
    huffman_decode_step(&hc);

    // Decode a run
    huffman_decode_run(&hc);

    // Clean up Huffman decoding
    huffman_decode_done(&hc);

    return 0;
}