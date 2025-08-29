// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bmp_load at bmp.c:30:5 in bmp.h
// bmp_save at bmp.c:71:5 in bmp.h
// bmp_free at bmp.c:102:6 in bmp.h
// yuv_to_rgb at color.c:15:6 in color.h
// rgb_to_yuv at color.c:32:6 in color.h
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

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    BMP *bmp = (BMP *)malloc(sizeof(BMP));
    if (bmp == NULL) return 0;

    // Initialize BMP structure with random data
    memset(bmp, 0, sizeof(BMP));

    // Load BMP from dummy file
    bmp_load(bmp, DUMMY_FILE);

    // Ensure the Data size is at least 3 to avoid out-of-bounds access
    if (Size < 3) {
        free(bmp);
        return 0;
    }

    // Fuzzing the jfif_encode function
    jfif_encode(bmp);

    // Fuzzing rgb_to_yuv and yuv_to_rgb with values from Data
    BYTE r = Data[0] % 256;
    BYTE g = Data[1] % 256;
    BYTE b = Data[2] % 256;
    int y, u, v;
    
    rgb_to_yuv(r, g, b, &y, &u, &v);
    
    BYTE r_out, g_out, b_out;
    yuv_to_rgb(y, u, v, &r_out, &g_out, &b_out);

    // Save BMP to dummy file
    bmp_save(bmp, DUMMY_FILE);

    // Free BMP structure
    bmp_free(bmp);
    free(bmp);

    return 0;
}