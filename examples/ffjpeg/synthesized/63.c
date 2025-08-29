// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// init_dct_module at dct.c:19:6 in dct.h
// init_fdct_ftab at dct.c:49:6 in dct.h
// init_idct_ftab at dct.c:63:6 in dct.h
// fdct2d8x8 at dct.c:78:6 in dct.h
// idct2d8x8 at dct.c:188:6 in dct.h
// quant_encode at quant.c:29:6 in quant.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "quant.h"
#include "dct.h"

int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 128) return 0; // Ensure enough data for initialization

    int ftab[64];
    int qtab[64];
    int du[64];

    // Initialize qtab and du with fuzz data
    for (int i = 0; i < 64; i++) {
        qtab[i] = Data[i];
        du[i] = Data[i + 64];
    }

    // Ensure no zero values in qtab for quant_encode
    for (int i = 0; i < 64; i++) {
        if (qtab[i] == 0) qtab[i] = 1;
    }

    // Initialize DCT module
    init_dct_module();

    // Initialize IDCT frequency table
    init_idct_ftab(ftab, qtab);

    // Initialize FDCT frequency table
    init_fdct_ftab(ftab, qtab);

    // Perform 2D DCT
    fdct2d8x8(du, ftab);

    // Perform quantization
    quant_encode(du, qtab);

    // Perform 2D IDCT
    idct2d8x8(du, ftab);

    return 0;
}