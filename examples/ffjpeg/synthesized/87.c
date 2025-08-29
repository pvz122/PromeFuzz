// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bitstr_getb at bitstr.c:245:5 in bitstr.h
// bitstr_get_bits at bitstr.c:299:5 in bitstr.h
// yuv_to_rgb at color.c:15:6 in color.h
// rgb_to_yuv at color.c:32:6 in color.h
// jfif_load at jfif.c:137:7 in jfif.h
// jfif_free at jfif.c:361:6 in jfif.h
// jfif_decode at jfif.c:375:5 in jfif.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "jfif.h"
#include "bitstr.h"

int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    // Create a dummy file for jfif_load
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Test jfif_load
    void *ctxt = jfif_load("./dummy_file");
    if (!ctxt) {
        remove("./dummy_file");
        return 0;
    }

    // Test bitstr_getb
    bitstr_getb(ctxt);

    // Test bitstr_get_bits
    bitstr_get_bits(ctxt, 8);

    // Test jfif_decode
    BMP pb;
    if (jfif_decode(ctxt, &pb) == 0) {
        // Free allocated memory in BMP structure
        if (pb.pdata) free(pb.pdata);
    }

    // Test yuv_to_rgb
    BYTE r, g, b;
    yuv_to_rgb(128, 128, 128, &r, &g, &b);

    // Test rgb_to_yuv
    int y, u, v;
    rgb_to_yuv(255, 255, 255, &y, &u, &v);

    // Cleanup
    if (ctxt) {
        // Free allocated memory in jfif context
        jfif_free(ctxt);
    }
    remove("./dummy_file");

    return 0;
}