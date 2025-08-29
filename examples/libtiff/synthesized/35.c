// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFStripSize at tif_strip.c:203:10 in tiffio.h
// TIFFRawStripSize at tif_strip.c:167:10 in tiffio.h
// TIFFWriteBufferSetup at tif_write.c:672:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFWriteRawStrip at tif_write.c:328:10 in tiffio.h
// TIFFWriteRawTile at tif_write.c:533:10 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <tiffio.h>

#define DUMMY_FILE "./dummy_file"

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    TIFF *tif;
    uint32_t tile = 0;
    uint32_t strip = 0;
    tmsize_t written_size;
    void *buffer;
    
    // Prepare dummy file
    int fd = open(DUMMY_FILE, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) return 0;
    close(fd);

    // Open TIFF file for writing
    tif = TIFFOpen(DUMMY_FILE, "w");
    if (!tif) return 0;

    // Initialize buffer with fuzz data
    buffer = malloc(Size);
    if (!buffer) {
        TIFFClose(tif);
        return 0;
    }
    memcpy(buffer, Data, Size);

    // Invoke target functions with fuzzing
    written_size = TIFFWriteRawTile(tif, tile, buffer, Size);
    written_size = TIFFWriteRawStrip(tif, strip, buffer, Size);
    written_size = TIFFWriteEncodedStrip(tif, strip, buffer, Size);
    written_size = TIFFStripSize(tif);
    written_size = TIFFRawStripSize(tif, strip);
    TIFFWriteBufferSetup(tif, buffer, Size);

    // Cleanup
    free(buffer);
    TIFFClose(tif);
    return 0;
}