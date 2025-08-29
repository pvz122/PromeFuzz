// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// init_fdct_ftab at dct.c:49:6 in dct.h
// init_idct_ftab at dct.c:63:6 in dct.h
// fdct2d8x8 at dct.c:78:6 in dct.h
// idct2d8x8 at dct.c:188:6 in dct.h
// quant_encode at quant.c:29:6 in quant.h
// quant_decode at quant.c:34:6 in quant.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "quant.h"
#include "dct.h"

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 128) return 0; // Ensure enough data for initialization

    int du[64];
    int qtab[64];
    int ftab[64];

    // Initialize du and qtab with fuzzed data
    for (int i = 0; i < 64; i++) {
        du[i] = (int)Data[i];
        qtab[i] = (int)Data[i + 64];
        // Ensure qtab[i] is not zero to avoid division by zero
        if (qtab[i] == 0) qtab[i] = 1;
    }

    // Test quant_decode
    quant_decode(du, qtab);

    // Test init_idct_ftab
    init_idct_ftab(ftab, qtab);

    // Test quant_encode
    quant_encode(du, qtab);

    // Test fdct2d8x8
    fdct2d8x8(du, ftab);

    // Test init_fdct_ftab
    init_fdct_ftab(ftab, qtab);

    // Test idct2d8x8
    idct2d8x8(du, ftab);

    return 0;
}