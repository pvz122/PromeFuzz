// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bmp_load at bmp.c:30:5 in bmp.h
// jfif_save at jfif.c:261:5 in jfif.h
// jfif_decode at jfif.c:375:5 in jfif.h
// jfif_encode at jfif.c:659:7 in jfif.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "jfif.h"
#include "bmp.h"

#define DUMMY_FILE "./dummy_file"

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    // Initialize BMP structure
    BMP bmp;
    
    // Prepare a dummy BMP file for loading
    FILE *dummy_file = fopen(DUMMY_FILE, "wb");
    if (dummy_file) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }

    // Load BMP from the dummy file
    if (bmp_load(&bmp, DUMMY_FILE) == 0) {
        // Encode BMP to JPEG
        void *jpeg_ctx = jfif_encode(&bmp);
        if (jpeg_ctx) {
            // Save JPEG to a file
            jfif_save(jpeg_ctx, "output.jpeg");
            // Decode JPEG back to BMP
            jfif_decode(jpeg_ctx, &bmp);
            // Free JPEG context
            free(jpeg_ctx);
        }
    }

    // Clean up
    remove(DUMMY_FILE);
    return 0;
}