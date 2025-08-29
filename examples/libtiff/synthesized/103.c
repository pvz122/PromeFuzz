// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFOpenOptionsAlloc at tif_open.c:80:18 in tiffio.h
// TIFFOpenOptionsFree at tif_open.c:87:6 in tiffio.h
// TIFFOpenOptionsSetMaxSingleMemAlloc at tif_open.c:94:6 in tiffio.h
// TIFFOpenOptionsSetWarnAboutUnknownTags at tif_open.c:115:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:233:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    // Step 1: Initialize TIFFOpenOptions
    TIFFOpenOptions *opts = TIFFOpenOptionsAlloc();
    if (opts == NULL) return 0;

    // Step 2: Prepare environment
    // Set random values from fuzz data
    int warn_about_unknown_tags = (Size > 0) ? Data[0] % 2 : 0;
    tmsize_t max_single_mem_alloc = (Size >= sizeof(tmsize_t) + 1) ? *(tmsize_t *)&Data[1] : 0;

    // Step 3: Invoke the target functions diversely
    TIFFOpenOptionsSetWarnAboutUnknownTags(opts, warn_about_unknown_tags);
    TIFFOpenOptionsSetMaxSingleMemAlloc(opts, max_single_mem_alloc);

    // Create a dummy file
    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Open the TIFF file with the options set
    TIFF *tiff = TIFFOpenExt(filename, "r", opts);
    if (tiff) {
        // Cleanup
        TIFFClose(tiff);
    }

    // Cleanup
    TIFFOpenOptionsFree(opts);
    return 0;
}