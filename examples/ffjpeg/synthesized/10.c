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

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    // Initialize BMP structure
    BMP *bmp = (BMP *)malloc(sizeof(BMP));
    if (bmp == NULL) return 0;

    // Create a dummy BMP image with random width and height
    int width = (Size % 1000) + 1; // Avoid zero width
    int height = (Size % 1000) + 1; // Avoid zero height
    if (bmp_create(bmp, width, height) != 0) {
        free(bmp);
        return 0;
    }

    // Load the BMP data from the fuzz input
    // Assuming Data is large enough to fill the BMP structure (for the sake of fuzzing)
    memcpy(bmp->pdata, Data, Size < (width * height * 3) ? Size : (width * height * 3));

    // Encode the BMP to JPEG
    void *jpeg_data = jfif_encode(bmp);
    
    // Save the JPEG to a dummy file
    const char *dummy_file = "./dummy_file";
    jfif_save(jpeg_data, (char *)dummy_file);

    // Clean up
    bmp_free(bmp);
    free(bmp);
    // Assuming jfif_encode allocates memory for jpeg_data that needs to be freed
    free(jpeg_data);

    return 0;
}