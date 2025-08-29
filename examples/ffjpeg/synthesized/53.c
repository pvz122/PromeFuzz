// This fuzz driver is generated for library ffjpeg, aiming to fuzz the following functions:
// bmp_load at bmp.c:30:5 in bmp.h
// bmp_save at bmp.c:71:5 in bmp.h
// jfif_load at jfif.c:137:7 in jfif.h
// jfif_save at jfif.c:261:5 in jfif.h
// jfif_free at jfif.c:361:6 in jfif.h
// jfif_decode at jfif.c:375:5 in jfif.h
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

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    // Initialize context and BMP structure
    void *context = NULL;
    BMP bmp;

    // Prepare dummy file
    FILE *file = fopen(DUMMY_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Fuzzing jfif_load
    context = jfif_load(DUMMY_FILE);
    if (context) {
        // Fuzzing jfif_decode
        jfif_decode(context, &bmp);
        // Fuzzing jfif_save
        jfif_save(context, DUMMY_FILE);
        // Cleanup
        jfif_free(context);
    }

    // Fuzzing bmp_load
    bmp_load(&bmp, DUMMY_FILE);
    // Fuzzing bmp_save
    bmp_save(&bmp, DUMMY_FILE);

    return 0;
}