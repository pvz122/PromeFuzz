// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bmp_load at bmp.c:30:5 in bmp.h
// jfif_save at jfif.c:261:5 in jfif.h
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

#define DUMMY_FILE "./dummy_file"

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    BMP bmp;
    void *jpeg_context = NULL;
    char *dummy_file = DUMMY_FILE;

    // Initialize BMP structure
    memset(&bmp, 0, sizeof(BMP));

    // Write the input data to a dummy file
    FILE *file = fopen(dummy_file, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Load BMP from the dummy file
    if (bmp_load(&bmp, dummy_file) == 0) {
        // Encode BMP to JPEG
        jpeg_context = jfif_encode(&bmp);
        if (jpeg_context) {
            // Save JPEG to the dummy file
            jfif_save(jpeg_context, dummy_file);
            // Decode JPEG back to BMP
            jfif_decode(jpeg_context, &bmp);
            // Free JPEG context
            jfif_free(jpeg_context);
        }
    }

    // Cleanup: Free BMP pdata if it was allocated
    if (bmp.pdata) {
        free(bmp.pdata);
        bmp.pdata = NULL;
    }

    return 0;
}