// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bmp_load at bmp.c:30:5 in bmp.h
// bmp_create at bmp.c:62:5 in bmp.h
// bmp_save at bmp.c:71:5 in bmp.h
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

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    BMP bmp;
    void *jpeg_data = NULL;
    int width = 100; // Arbitrary width
    int height = 100; // Arbitrary height

    // Initialize BMP structure
    if (bmp_create(&bmp, width, height) != 0) {
        return 0; // Failed to create BMP
    }

    // Load random data into BMP for fuzzing
    if (Size < sizeof(bmp)) {
        memcpy(&bmp, Data, Size);
    } else {
        memcpy(&bmp, Data, sizeof(bmp));
    }

    // Save BMP to dummy file
    bmp_save(&bmp, DUMMY_FILE);

    // Load BMP from file
    bmp_load(&bmp, DUMMY_FILE);

    // Encode BMP to JPEG
    jpeg_data = jfif_encode(&bmp);
    
    // Save JPEG to file if encoding was successful
    if (jpeg_data) {
        jfif_save(jpeg_data, "output.jpg");
        free(jpeg_data); // Free the allocated jpeg_data after saving
    }

    // Free resources
    bmp_free(&bmp);

    return 0;
}