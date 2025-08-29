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

int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    BMP bmp;
    void *jpeg_data;
    char *dummy_file = "./dummy_file";

    if (bmp_create(&bmp, 100, 100) != 0) {
        return 0;
    }

    // Copy fuzz data into BMP pixel buffer only
    size_t bmp_size = (size_t)bmp.stride * bmp.height;
    size_t copy_size = Size < bmp_size ? Size : bmp_size;
    if (copy_size > 0) {
        memcpy(bmp.pdata, Data, copy_size);
    }

    jpeg_data = jfif_encode(&bmp);
    jfif_save(jpeg_data, dummy_file);

    bmp_free(&bmp);
    free(jpeg_data);

    return 0;
}