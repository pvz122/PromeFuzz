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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "jfif.h"
#include "bmp.h"

#define DUMMY_FILE "./dummy_file"

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    BMP bmp;
    void *jpeg_data;
    int width = 0, height = 0;
    
    // Initialize BMP structure with random width and height
    width = (Size % 1000) + 1; // Ensure width is at least 1
    height = (Size % 1000) + 1; // Ensure height is at least 1
    bmp_create(&bmp, width, height);

    // Load BMP data from the fuzz input
    if (Size > sizeof(bmp)) {
        memcpy(&bmp, Data, sizeof(bmp) < Size ? sizeof(bmp) : Size);
    }

    // Encode BMP to JPEG
    jpeg_data = jfif_encode(&bmp);

    // Save JPEG to file
    jfif_save(jpeg_data, DUMMY_FILE);

    // Free BMP structure
    bmp_free(&bmp);

    // Cleanup JPEG data if necessary (depends on jfif_encode implementation)
    // Assuming there is a function to free jpeg_data if allocated
    // free_jpeg_data(jpeg_data);

    return 0;
}