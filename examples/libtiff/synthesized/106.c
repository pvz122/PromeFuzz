// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFOpenOptionsAlloc at tif_open.c:80:18 in tiffio.h
// TIFFOpenOptionsFree at tif_open.c:87:6 in tiffio.h
// TIFFOpenOptionsSetMaxSingleMemAlloc at tif_open.c:94:6 in tiffio.h
// TIFFOpenOptionsSetMaxCumulatedMemAlloc at tif_open.c:106:6 in tiffio.h
// TIFFOpenOptionsSetWarnAboutUnknownTags at tif_open.c:115:6 in tiffio.h
// TIFFOpenOptionsSetErrorHandlerExtR at tif_open.c:121:6 in tiffio.h
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

int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size) {
    // Allocate TIFFOpenOptions
    TIFFOpenOptions *opts = TIFFOpenOptionsAlloc();
    if (!opts) return 0;

    // Initialize opts with random values from input data
    opts->warn_about_unknown_tags = Data[0] % 2; // Set to 0 or 1

    // Ensure Size is large enough to read tmsize_t values
    if (Size >= sizeof(tmsize_t) * 2) {
        opts->max_single_mem_alloc = *(tmsize_t*)Data % (1 << 30); // Some limit in bytes
        opts->max_cumulated_mem_alloc = *(tmsize_t*)(Data + sizeof(tmsize_t)) % (1 << 30); // Some limit in bytes
    } else {
        opts->max_single_mem_alloc = 0; // Default value if not enough data
        opts->max_cumulated_mem_alloc = 0; // Default value if not enough data
    }

    // Set warning about unknown tags
    TIFFOpenOptionsSetWarnAboutUnknownTags(opts, opts->warn_about_unknown_tags);

    // Set maximum single memory allocation
    TIFFOpenOptionsSetMaxSingleMemAlloc(opts, opts->max_single_mem_alloc);

    // Set maximum cumulated memory allocation
    TIFFOpenOptionsSetMaxCumulatedMemAlloc(opts, opts->max_cumulated_mem_alloc);

    // Set error handler (using a NULL handler for simplicity)
    TIFFOpenOptionsSetErrorHandlerExtR(opts, NULL, NULL);

    // Free the options after use
    TIFFOpenOptionsFree(opts);

    return 0;
}