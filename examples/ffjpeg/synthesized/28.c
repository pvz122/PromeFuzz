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

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    BMP bmp;
    void *jpeg_data;
    int width = 100; // Arbitrary width
    int height = 100; // Arbitrary height

    // Step 1: Initialize BMP structure
    if (bmp_create(&bmp, width, height) != 0) {
        return 0; // Failed to create BMP
    }

    // Step 2: Load BMP data from the fuzz input
    if (Size < (size_t)(width * height * 3)) {
        memcpy(bmp.pdata, Data, Size); // Ensure we don't overflow
    } else {
        memcpy(bmp.pdata, Data, width * height * 3); // Copy only the valid size
    }

    // Step 3: Encode BMP to JPEG
    jpeg_data = jfif_encode(&bmp);
    
    // Step 4: Save JPEG data to a file
    jfif_save(jpeg_data, DUMMY_FILE);

    // Cleanup
    bmp_free(&bmp);
    free(jpeg_data);

    return 0;
}