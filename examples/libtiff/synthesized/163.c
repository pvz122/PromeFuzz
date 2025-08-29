// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFFlushData at tif_flush.c:146:5 in tiffio.h
// TIFFSetFileno at tif_open.c:818:5 in tiffio.h
// TIFFSetMode at tif_open.c:848:5 in tiffio.h
// TIFFSetupStrips at tif_write.c:553:5 in tiffio.h
// TIFFWriteCheck at tif_write.c:600:5 in tiffio.h
// TIFFCheckpointDirectory at tif_dirwrite.c:289:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_163(const uint8_t *Data, size_t Size) {
    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (tif == NULL) {
        return 0; // Failed to open TIFF file
    }

    // Fuzzing TIFFSetMode
    int mode = (Size > 0) ? (Data[0] % 3) : 0; // Random mode (0, 1, or 2)
    int prev_mode = TIFFSetMode(tif, mode);

    // Fuzzing TIFFFlushData
    TIFFFlushData(tif);

    // Fuzzing TIFFSetupStrips
    TIFFSetupStrips(tif);

    // Fuzzing TIFFSetFileno
    int file_no = (Size > 1) ? (Data[1] % 1000) : 0; // Random file descriptor
    int prev_fileno = TIFFSetFileno(tif, file_no);

    // Fuzzing TIFFWriteCheck
    char *name = (Size > 2) ? (char *)malloc(Size) : NULL; // Allocate memory for name
    if (name) {
        memcpy(name, Data + 2, Size - 2);
        name[Size - 2] = '\0'; // Null-terminate the string
    } else {
        name = "default_name"; // Use default name if allocation fails
    }
    TIFFWriteCheck(tif, 0, name);

    // Free allocated name if it was created
    if (name != "default_name") {
        free(name);
    }

    // Fuzzing TIFFCheckpointDirectory
    TIFFCheckpointDirectory(tif);

    // Cleanup
    TIFFClose(tif);
    return 0;
}