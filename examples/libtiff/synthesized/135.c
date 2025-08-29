// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFGetTagListCount at tif_extension.c:34:5 in tiffio.h
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFCreateCustomDirectory at tif_dir.c:1703:5 in tiffio.h
// TIFFCreateEXIFDirectory at tif_dir.c:1731:5 in tiffio.h
// TIFFWriteCustomDirectory at tif_dirwrite.c:300:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFSetTagExtender at tif_dir.c:1674:16 in tiffio.h
// TIFFMergeFieldInfo at tif_dirinfo.c:1147:5 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "tiffio.h"

typedef struct _TIFFFieldArray {
    uint32_t allocated_size; /* size of the array */
    uint32_t count; /* number of elements in fields array */
    TIFFField *fields; /* actual field info */
} TIFFFieldArray;

int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size) {
    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) return 0;

    // Create an EXIF directory
    if (TIFFCreateEXIFDirectory(tif) == 1) {
        // Prepare a custom directory
        TIFFFieldArray *fieldArray = (TIFFFieldArray *)malloc(sizeof(TIFFFieldArray));
        if (fieldArray) {
            fieldArray->allocated_size = 0;
            fieldArray->count = 0;
            fieldArray->fields = NULL;

            // Create custom directory
            TIFFCreateCustomDirectory(tif, fieldArray);

            // Write custom directory
            uint64_t dirOffset;
            TIFFWriteCustomDirectory(tif, &dirOffset);

            // Set a tag extender (example with NULL, replace with actual function if needed)
            TIFFSetTagExtender(NULL);

            // Merge field info (dummy data)
            TIFFFieldInfo fieldInfo;
            TIFFMergeFieldInfo(tif, &fieldInfo, 1);

            // Get tag list count
            int tagCount = TIFFGetTagListCount(tif);

            // Clean up
            free(fieldArray);
        }
    }

    // Close TIFF file
    TIFFClose(tif);
    return 0;
}