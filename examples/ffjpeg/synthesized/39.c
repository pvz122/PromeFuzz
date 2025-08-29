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
#include "quant.h"
#include "zigzag.h"
#include "dct.h"
#include "jfif.h"

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 64 * 4 * 3) return 0; // Ensure enough data for all arrays (du, qtab, ftab)

    int du[64];
    int qtab[64];
    int ftab[64];
    BMP pb;
    void *ctxt = NULL;

    // Initialize arrays with fuzzed data
    memcpy(du, Data, 64 * sizeof(int));
    memcpy(qtab, Data + 64 * sizeof(int), 64 * sizeof(int));
    memcpy(ftab, Data + 128 * sizeof(int), 64 * sizeof(int));

    // Ensure no division by zero in quant_decode
    for (int i = 0; i < 64; i++) {
        if (qtab[i] == 0) qtab[i] = 1; // Avoid division by zero
    }

    // Call target functions
    quant_decode(du, qtab);
    zigzag_decode(du);
    init_idct_ftab(ftab, qtab);
    quant_encode(du, qtab);
    idct2d8x8(du, ftab);

    // Decode JPEG to BMP
    jfif_decode(ctxt, &pb);

    return 0;
}