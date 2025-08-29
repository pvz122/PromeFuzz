// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
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

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    BMP bmp;
    void *jpeg_data;
    char *file_path = DUMMY_FILE;

    // Initialize BMP structure
    if (Size < sizeof(int) * 2) return 0; // Ensure enough data for width and height
    int width = *((int*)Data);
    int height = *((int*)(Data + sizeof(int)));

    // Create BMP
    if (bmp_create(&bmp, width, height) != 0) return 0;

    // Load BMP data from fuzz input
    memcpy(bmp.pdata, Data + sizeof(int) * 2, Size - sizeof(int) * 2);

    // Encode BMP to JPEG
    jpeg_data = jfif_encode(&bmp);
    if (jpeg_data != NULL) {
        // Save JPEG data to file
        jfif_save(jpeg_data, file_path);
        free(jpeg_data);
    }

    // Save BMP to file (for testing purposes)
    bmp_save(&bmp, file_path);

    // Free BMP structure
    bmp_free(&bmp);

    return 0;
}