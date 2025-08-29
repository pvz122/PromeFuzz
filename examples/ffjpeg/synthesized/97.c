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

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    // Create a dummy file for jfif_load
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Test jfif_load
    void *ctxt = jfif_load("./dummy_file");
    if (ctxt) {
        // Test jfif_decode
        BMP pb;
        memset(&pb, 0, sizeof(BMP));
        jfif_decode(ctxt, &pb);

        // Free allocated memory in BMP structure
        if (pb.pdata) {
            free(pb.pdata);
        }

        // Test bitstr_getb and bitstr_get_bits
        bitstr_getb(ctxt);
        bitstr_get_bits(ctxt, 8);

        // Test yuv_to_rgb and rgb_to_yuv
        BYTE r, g, b;
        int y, u, v;
        yuv_to_rgb(128, 128, 128, &r, &g, &b);
        rgb_to_yuv(r, g, b, &y, &u, &v);

        // Clean up
        if (ctxt) {
            // Free the context and its internal data
            jfif_free(ctxt);
        }
    }

    // Remove the dummy file
    remove("./dummy_file");

    return 0;
}