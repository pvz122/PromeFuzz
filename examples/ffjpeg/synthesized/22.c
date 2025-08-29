// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bmp_create at bmp.c:62:5 in bmp.h
// bmp_free at bmp.c:102:6 in bmp.h
// jfif_save at jfif.c:261:5 in jfif.h
// jfif_encode at jfif.c:659:7 in jfif.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "jfif.h"
#include "bmp.h"

#define DUMMY_FILE "./dummy_file"

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    BMP bmp;
    void *jpeg_data;
    int width = 100;  // Arbitrary width
    int height = 100; // Arbitrary height

    // Initialize BMP structure
    if (bmp_create(&bmp, width, height) != 0) {
        return 0; // Failed to create BMP
    }

    // Load BMP data from the fuzz input
    if (Size > sizeof(bmp.pdata)) {
        Size = sizeof(bmp.pdata);
    }
    memcpy(bmp.pdata, Data, Size);

    // Encode BMP to JPEG
    jpeg_data = jfif_encode(&bmp);
    if (jpeg_data) {
        // Save the JPEG data to a file
        jfif_save(jpeg_data, DUMMY_FILE);
        free(jpeg_data);
    }

    // Free BMP structure
    bmp_free(&bmp);

    return 0;
}