// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// init_fdct_ftab at dct.c:49:6 in dct.h
// init_idct_ftab at dct.c:63:6 in dct.h
// idct2d8x8 at dct.c:188:6 in dct.h
// jfif_decode at jfif.c:375:5 in jfif.h
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

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 192 * sizeof(int)) {
        return 0;
    }

    int ftab[64];
    int qtab[64];
    int du[64];
    int data[64];

    // Initialize tables with fuzzed data
    memcpy(qtab, Data, 64 * sizeof(int));
    memcpy(du, Data + 64 * sizeof(int), 64 * sizeof(int));
    memcpy(data, Data + 128 * sizeof(int), 64 * sizeof(int));

    // Initialize IDCT frequency table
    init_idct_ftab(ftab, qtab);

    // Perform 2D IDCT on 8x8 block
    idct2d8x8(du, ftab);

    // Initialize FDCT frequency table
    init_fdct_ftab(ftab, qtab);

    // Reverse quantization process
    quant_decode(du, qtab);

    // Convert zigzag-ordered array back to 2D block
    zigzag_decode(data);

    // Decode JPEG image into BMP format
    BMP pb;
    void *ctxt = malloc(1024); // Allocate dummy context
    if (ctxt) {
        jfif_decode(ctxt, &pb);
        free(ctxt);
    }

    return 0;
}