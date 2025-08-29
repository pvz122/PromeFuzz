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
#include "dct.h"
#include "zigzag.h"
#include "jfif.h"
#include "quant.h"

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 192) return 0; // Ensure enough data for initialization (64 + 64 + 64 = 192)

    int ftab[64];
    int qtab[64];
    int du[64];
    BMP pb;
    void *ctxt = NULL;

    // Initialize tables with fuzzed data
    for (int i = 0; i < 64; i++) {
        if (i + 64 < Size) ftab[i] = (int)Data[i];
        if (i + 128 < Size) qtab[i] = (int)Data[i + 64];
        if (i + 192 < Size) du[i] = (int)Data[i + 128];
    }

    // Ensure no division by zero in quantization table
    for (int i = 0; i < 64; i++) {
        if (qtab[i] == 0) qtab[i] = 1; // Avoid division by zero
    }

    // Call target functions
    init_idct_ftab(ftab, qtab);
    quant_encode(du, qtab);
    idct2d8x8(du, ftab);
    quant_decode(du, qtab);
    zigzag_decode(du);
    jfif_decode(ctxt, &pb);

    return 0;
}