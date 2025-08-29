// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bmp_create at bmp.c:62:5 in bmp.h
// bmp_free at bmp.c:102:6 in bmp.h
// jfif_encode at jfif.c:659:7 in jfif.h
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
#include "bmp.h"

#define DUMMY_FILE "./dummy_file"

int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    BMP bmp;
    int width = 100; // Example width
    int height = 100; // Example height
    int stride = width * sizeof(BYTE); // Assuming 1 byte per pixel

    // Initialize BMP structure
    if (bmp_create(&bmp, width, height) != 0) {
        return 0; // Failed to create BMP
    }

    // Check if the input data is large enough to fill the BMP data
    if (Size >= stride * height) {
        memcpy(bmp.pdata, Data, stride * height); // Safely copy data
    } else {
        memcpy(bmp.pdata, Data, Size); // Copy only available data
    }

    // Encode BMP to JPEG
    jfif_encode(&bmp);

    // Free BMP structure
    bmp_free(&bmp);

    return 0;
}