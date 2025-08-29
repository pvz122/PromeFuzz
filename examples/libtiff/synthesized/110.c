// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFError at tif_error.c:46:6 in tiffio.h
// TIFFWarningExt at tif_warning.c:63:6 in tiffio.h
// TIFFWarningExtR at tif_warning.c:80:6 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:233:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tiffio.h"

typedef struct TIFFOpenOptions {
    TIFFErrorHandlerExtR errorhandler; /* may be NULL */
    void *errorhandler_user_data; /* may be NULL */
    TIFFErrorHandlerExtR warnhandler; /* may be NULL */
    void *warnhandler_user_data; /* may be NULL */
    tmsize_t max_single_mem_alloc; /* in bytes. 0 for unlimited */
    tmsize_t max_cumulated_mem_alloc; /* in bytes. 0 for unlimited */
    int warn_about_unknown_tags;
} TIFFOpenOptions;

int LLVMFuzzerTestOneInput_110(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a dummy TIFF file
    FILE *dummy_file = fopen("./dummy_file", "wb+");
    if (!dummy_file) return 0;
    fwrite(Data, 1, Size, dummy_file);
    fclose(dummy_file);

    // Initialize TIFFOpenOptions
    TIFFOpenOptions *opts = (TIFFOpenOptions *)malloc(sizeof(TIFFOpenOptions));
    if (opts) {
        memset(opts, 0, sizeof(TIFFOpenOptions));
    }

    // Open the TIFF file
    TIFF *tif = TIFFOpenExt("./dummy_file", "r", opts);
    if (tif) {
        // Invoke TIFFWarningExt
        TIFFWarningExt((thandle_t)tif, "Warning", "This is a test warning.");

        // Invoke TIFFError
        TIFFError("Error", "This is a test error.");

        // Invoke TIFFWarningExtR
        TIFFWarningExtR(tif, "Warning", "This is a test warning R.");

        // Invoke TIFFErrorExtR
        TIFFErrorExtR(tif, "Error", "This is a test error R.");

        // Cleanup
        TIFFClose(tif);
    }

    // Free options
    free(opts);
    
    return 0;
}