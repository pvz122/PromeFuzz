// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// init_idct_ftab at dct.c:63:6 in dct.h
// idct2d8x8 at dct.c:188:6 in dct.h
// jfif_decode at jfif.c:375:5 in jfif.h
// quant_encode at quant.c:29:6 in quant.h
// quant_decode at quant.c:34:6 in quant.h
// zigzag_decode at zigzag.c:24:6 in zigzag.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "dct.h"
#include "zigzag.h"
#include "jfif.h"
#include "quant.h"

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 64 * 4 * 3) return 0; // Ensure enough data for ftab, qtab, and du

    int ftab[64];
    int qtab[64];
    int du[64];

    // Initialize ftab, qtab, and du with fuzzed data
    memcpy(ftab, Data, 64 * sizeof(int));
    memcpy(qtab, Data + 64 * sizeof(int), 64 * sizeof(int));
    memcpy(du, Data + 128 * sizeof(int), 64 * sizeof(int));

    // Initialize IDCT frequency table
    init_idct_ftab(ftab, qtab);

    // Apply quantization
    quant_encode(du, qtab);

    // Perform 2D IDCT
    idct2d8x8(du, ftab);

    // Reverse quantization
    quant_decode(du, qtab);

    // Convert zigzag-ordered array back to 2D block
    zigzag_decode(du);

    // Decode JPEG to BMP (dummy context and BMP structure)
    BMP pb;
    void *ctxt = malloc(1);
    if (ctxt) {
        jfif_decode(ctxt, &pb);
        free(ctxt);
    }

    return 0;
}