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
#include <tiffio.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there's enough data for the file descriptor

    // Initialize a TIFF structure
    TIFF *tif = TIFFOpen("./dummy_file", "w");
    if (!tif) return 0;

    // Prepare data for fuzzing
    int mode = Data[0] % 3; // Random mode: 0, 1, or 2
    TIFFSetMode(tif, mode);

    // Fuzz TIFFFlushData
    TIFFFlushData(tif);

    // Fuzz TIFFSetupStrips
    TIFFSetupStrips(tif);

    // Fuzz TIFFSetFileno
    int new_fd = *(int *)Data % 65536; // Random file descriptor
    TIFFSetFileno(tif, new_fd);

    // Fuzz TIFFWriteCheck with a valid string
    const char *tag = (const char *)(Data + 1); // Use data starting from the second byte
    size_t tag_length = Size > 1 ? Size - 1 : 1; // Ensure at least one byte for the tag
    char *tag_buffer = (char *)malloc(tag_length + 1);
    if (tag_buffer) {
        memcpy(tag_buffer, tag, tag_length);
        tag_buffer[tag_length] = '\0'; // Null-terminate the string
        TIFFWriteCheck(tif, 0, tag_buffer);
        free(tag_buffer);
    }

    // Fuzz TIFFCheckpointDirectory
    TIFFCheckpointDirectory(tif);

    // Cleanup
    TIFFClose(tif);
    return 0;
}