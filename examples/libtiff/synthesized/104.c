// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFSetErrorHandlerExt at tif_error.c:39:21 in tiffio.h
// TIFFWarningExtR at tif_warning.c:80:6 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFOpenOptionsSetWarningHandlerExtR at tif_open.c:129:6 in tiffio.h
// TIFFOpenExt at tif_unix.c:233:7 in tiffio.h
// TIFFSetTagExtender at tif_dir.c:1674:16 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

typedef struct TIFFOpenOptions {
    TIFFErrorHandlerExtR errorhandler; /* may be NULL */
    void *errorhandler_user_data; /* may be NULL */
    TIFFErrorHandlerExtR warnhandler; /* may be NULL */
    void *warnhandler_user_data; /* may be NULL */
    tmsize_t max_single_mem_alloc; /* in bytes. 0 for unlimited */
    tmsize_t max_cumulated_mem_alloc; /* in bytes. 0 for unlimited */
    int warn_about_unknown_tags;
} TIFFOpenOptions;

int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
    TIFFExtendProc oldExtendProc = NULL;
    TIFFErrorHandlerExt oldErrorHandler = NULL;
    TIFF *tif = NULL;
    TIFFOpenOptions *opts = NULL;
    char *filename = "./dummy_file";
    FILE *dummyFile = fopen(filename, "wb");

    if (!dummyFile) return 0;

    fwrite(Data, 1, Size, dummyFile);
    fclose(dummyFile);

    opts = (TIFFOpenOptions *)malloc(sizeof(TIFFOpenOptions));
    if (opts) {
        memset(opts, 0, sizeof(TIFFOpenOptions));
    }

    oldExtendProc = TIFFSetTagExtender(NULL);
    oldErrorHandler = TIFFSetErrorHandlerExt(NULL);

    tif = TIFFOpenExt(filename, "r", opts);
    if (tif) {
        TIFFWarningExtR(tif, "Warning", "This is a test warning");
        TIFFErrorExtR(tif, "Error", "This is a test error");
        TIFFClose(tif);
    }

    if (opts) {
        TIFFOpenOptionsSetWarningHandlerExtR(opts, NULL, NULL);
        free(opts);
    }

    TIFFSetTagExtender(oldExtendProc);
    TIFFSetErrorHandlerExt(oldErrorHandler);

    return 0;
}