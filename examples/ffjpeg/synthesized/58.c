// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// huffman_decode_done at huffman.c:328:6 in huffman.h
// huffman_decode_run at huffman.c:333:6 in huffman.h
// huffman_decode_init at huffman.c:300:6 in huffman.h
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
#include "huffman.h"
#include "jfif.h"

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    // Write the input data to a dummy file
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Load the JPEG file
    void *ctxt = jfif_load("./dummy_file");
    if (!ctxt) return 0;

    // Decode the JPEG file
    BMP pb;
    int result = jfif_decode(ctxt, &pb);
    if (result != 0) {
        jfif_free(ctxt);
        return 0;
    }

    // Free BMP data to fix memory leak
    if (pb.pdata) {
        free(pb.pdata);
    }

    // Initialize Huffman decoder
    HUFCODEC hc;
    huffman_decode_init(&hc);

    // Run Huffman decoding
    BOOL decode_result = huffman_decode_run(&hc);
    if (!decode_result) {
        huffman_decode_done(&hc);
        jfif_free(ctxt);
        return 0;
    }

    // Clean up
    huffman_decode_done(&hc);
    jfif_free(ctxt);

    return 0;
}