// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bmp_load at bmp.c:30:5 in bmp.h
// bmp_create at bmp.c:62:5 in bmp.h
// bmp_free at bmp.c:102:6 in bmp.h
// jfif_free at jfif.c:361:6 in jfif.h
// jfif_decode at jfif.c:375:5 in jfif.h
// jfif_encode at jfif.c:659:7 in jfif.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "jfif.h"
#include "bmp.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    // Write the input data to a dummy file
    FILE *fp = fopen("./dummy_file", "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Initialize BMP structure
    BMP bmp;
    if (bmp_create(&bmp, 100, 100) != 0) {
        return 0;
    }

    // Load BMP from the dummy file
    if (bmp_load(&bmp, "./dummy_file") != 0) {
        bmp_free(&bmp);
        return 0;
    }

    // Encode BMP to JPEG
    void *jpeg_context = jfif_encode(&bmp);
    if (!jpeg_context) {
        bmp_free(&bmp);
        return 0;
    }

    // Decode JPEG back to BMP
    BMP decoded_bmp;
    if (bmp_create(&decoded_bmp, 100, 100) != 0) {
        jfif_free(jpeg_context);
        bmp_free(&bmp);
        return 0;
    }

    if (jfif_decode(jpeg_context, &decoded_bmp) != 0) {
        jfif_free(jpeg_context);
        bmp_free(&bmp);
        bmp_free(&decoded_bmp);
        return 0;
    }

    // Clean up
    jfif_free(jpeg_context);
    bmp_free(&bmp);
    bmp_free(&decoded_bmp);

    // Remove the dummy file
    remove("./dummy_file");

    return 0;
}