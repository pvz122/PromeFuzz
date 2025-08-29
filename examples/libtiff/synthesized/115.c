// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFError at tif_error.c:46:6 in tiffio.h
// TIFFErrorExt at tif_error.c:63:6 in tiffio.h
// TIFFWarning at tif_warning.c:46:6 in tiffio.h
// TIFFWarningExt at tif_warning.c:63:6 in tiffio.h
// TIFFWarningExtR at tif_warning.c:80:6 in tiffio.h
// TIFFErrorExtR at tif_error.c:107:6 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("./dummy_file", "w");
    if (!tif) return 0;

    // Prepare dummy data for the TIFF structure
    char warning_msg[256];
    char error_msg[256];

    // Ensure Data is null-terminated and does not exceed buffer size
    size_t warning_size = Size < sizeof(warning_msg) - 1 ? Size : sizeof(warning_msg) - 1;
    size_t error_size = Size < sizeof(error_msg) - 1 ? Size : sizeof(error_msg) - 1;

    memcpy(warning_msg, Data, warning_size);
    warning_msg[warning_size] = '\0'; // Null-terminate the string

    memcpy(error_msg, Data, error_size);
    error_msg[error_size] = '\0'; // Null-terminate the string

    // Invoke target functions with fuzzed data
    TIFFWarningExt(tif, "Fuzzing Warning", warning_msg);
    TIFFError("Fuzzing Error", error_msg);
    TIFFWarningExtR(tif, "Fuzzing Warning R", warning_msg);
    TIFFErrorExtR(tif, "Fuzzing Error R", error_msg);
    TIFFErrorExt((thandle_t)tif, "Fuzzing Error Ext", error_msg);
    TIFFWarning("Fuzzing Warning", warning_msg);

    // Cleanup
    TIFFClose(tif);
    return 0;
}