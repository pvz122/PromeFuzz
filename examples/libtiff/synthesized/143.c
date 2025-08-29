// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFGetVersion at tif_version.c:28:13 in tiffio.h
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFError at tif_error.c:46:6 in tiffio.h
// TIFFErrorExt at tif_error.c:63:6 in tiffio.h
// TIFFWarning at tif_warning.c:46:6 in tiffio.h
// TIFFWarningExt at tif_warning.c:63:6 in tiffio.h
// TIFFSetErrorHandler at tif_error.c:32:18 in tiffio.h
// TIFFSetWarningHandler at tif_warning.c:32:18 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "tiffio.h"

static void customWarningHandler(const char* module, const char* fmt, va_list ap) {
    fprintf(stderr, "Warning from %s: ", module);
    vfprintf(stderr, fmt, ap);
}

static void customErrorHandler(const char* module, const char* fmt, va_list ap) {
    fprintf(stderr, "Error from %s: ", module);
    vfprintf(stderr, fmt, ap);
}

int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size) {
    // Initialize a TIFF object
    TIFF *tif = TIFFOpen("./dummy_file", "w");
    if (!tif) {
        return 0; // Failed to open TIFF
    }

    // Set custom warning and error handlers
    TIFFSetWarningHandler(customWarningHandler);
    TIFFSetErrorHandler(customErrorHandler);

    // Fuzzing for TIFFWarningExt
    if (Size > 0) {
        TIFFWarningExt((thandle_t)tif, "Fuzzing", "Warning: %.*s", (int)Size, Data);
    }

    // Fuzzing for TIFFError
    if (Size > 0) {
        TIFFError("Fuzzing", "Error: %.*s", (int)Size, Data);
    }

    // Fuzzing for TIFFErrorExt
    if (Size > 0) {
        TIFFErrorExt((thandle_t)tif, "Fuzzing", "ErrorExt: %.*s", (int)Size, Data);
    }

    // Fuzzing for TIFFWarning
    if (Size > 0) {
        TIFFWarning("Fuzzing", "Warning: %.*s", (int)Size, Data);
    }

    // Fuzzing for TIFFGetVersion
    const char *version = TIFFGetVersion();
    if (version) {
        printf("LibTIFF version: %s\n", version);
    }

    // Clean up
    TIFFClose(tif);
    return 0;
}