// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFGetVersion at tif_version.c:28:13 in tiffio.h
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFError at tif_error.c:46:6 in tiffio.h
// TIFFErrorExt at tif_error.c:63:6 in tiffio.h
// TIFFWarning at tif_warning.c:46:6 in tiffio.h
// TIFFWarningExt at tif_warning.c:63:6 in tiffio.h
// TIFFWarningExtR at tif_warning.c:80:6 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_173(const uint8_t *Data, size_t Size) {
    // Initialize TIFF handle
    TIFF *tiff = TIFFOpen("./dummy_file", "w");
    if (!tiff) {
        return 0;
    }

    // Prepare data for fuzzing
    char warning_msg[256];
    char error_msg[256];

    // Ensure we don't overflow the buffers
    size_t warning_size = Size < sizeof(warning_msg) - 1 ? Size : sizeof(warning_msg) - 1;
    size_t error_size = Size < sizeof(error_msg) - 1 ? Size : sizeof(error_msg) - 1;

    // Copy data safely
    memcpy(warning_msg, Data, warning_size);
    warning_msg[warning_size] = '\0'; // Null-terminate

    // Adjust error size to avoid accessing out of bounds
    size_t error_offset = Size > 1 ? Size / 2 : 0;
    size_t error_copy_size = (Size - error_offset < error_size) ? (Size - error_offset) : error_size;

    memcpy(error_msg, Data + error_offset, error_copy_size);
    error_msg[error_copy_size] = '\0'; // Null-terminate

    // Fuzzing TIFFWarningExt
    TIFFWarningExt((thandle_t)tiff, "Warning", warning_msg);

    // Fuzzing TIFFError
    TIFFError("Error", error_msg);

    // Fuzzing TIFFWarningExtR
    TIFFWarningExtR(tiff, "WarningR", warning_msg);

    // Fuzzing TIFFErrorExt
    TIFFErrorExt((thandle_t)tiff, "ErrorExt", error_msg);

    // Fuzzing TIFFWarning
    TIFFWarning("WarningGlobal", warning_msg);

    // Fuzzing TIFFGetVersion
    const char *version = TIFFGetVersion();
    if (version) {
        // Do something with version if needed
    }

    // Cleanup
    TIFFClose(tiff);
    return 0;
}