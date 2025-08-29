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

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    // Initialize BMP structure
    BMP bmp;
    
    // Create a BMP image with arbitrary width and height
    int width = 100; // Example width
    int height = 100; // Example height
    if (bmp_create(&bmp, width, height) != 0) {
        return 0; // Failed to create BMP
    }

    // Load BMP data from the input data, ensuring we do not overflow
    size_t data_size = (Size < bmp.stride * height) ? Size : bmp.stride * height;
    memcpy(bmp.pdata, Data, data_size);

    // Encode the BMP to JPEG
    void *jpeg_data = jfif_encode(&bmp);
    
    // Save the JPEG data to a file
    if (jpeg_data) {
        jfif_save(jpeg_data, DUMMY_FILE);
    }
    
    // Free BMP memory
    bmp_free(&bmp);

    // Free JPEG data if necessary
    if (jpeg_data) {
        free(jpeg_data); // Assuming jpeg_data needs to be freed
    }

    return 0;
}