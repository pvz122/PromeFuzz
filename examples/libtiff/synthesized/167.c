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
#include <fcntl.h>
#include <unistd.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_167(const uint8_t *Data, size_t Size) {
    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (tif == NULL) {
        return 0; // Failed to open TIFF
    }

    // Fuzzing for TIFFSetMode
    int mode = Data[0] % 3; // Random mode (0, 1, or 2)
    TIFFSetMode(tif, mode);

    // Fuzzing for TIFFFlushData
    TIFFFlushData(tif);

    // Fuzzing for TIFFSetupStrips
    TIFFSetupStrips(tif);

    // Ensure Data has enough size before accessing
    if (Size > 1) {
        // Fuzzing for TIFFSetFileno
        int fd = (Data[1] % 1024); // Random file descriptor
        TIFFSetFileno(tif, fd);
    }

    // Fuzzing for TIFFWriteCheck
    if (Size > 2) {
        // Create a string for name using a valid length
        char name[16];
        size_t name_len = (Size - 2 < sizeof(name) - 1) ? Size - 2 : sizeof(name) - 1;
        memcpy(name, &Data[2], name_len);
        name[name_len] = '\0'; // Null-terminate the string
        TIFFWriteCheck(tif, 0, name);
    }

    // Fuzzing for TIFFCheckpointDirectory
    TIFFCheckpointDirectory(tif);

    // Cleanup
    TIFFClose(tif);
    return 0;
}