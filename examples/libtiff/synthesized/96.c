// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
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
#include <tiffio.h>
#include <fcntl.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    TIFF *tif;
    uint32_t strip = 0;
    tmsize_t rawSize;
    void *dataBuffer;
    
    // Prepare a dummy TIFF file
    int fd = open("./dummy_file", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) return 0;
    close(fd);
    
    // Open the TIFF file
    tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) return 0;

    // Initialize strip size
    rawSize = TIFFRawStripSize(tif, strip);
    
    // Create buffer for writing raw data
    dataBuffer = malloc(rawSize);
    if (dataBuffer) {
        // Fill buffer with fuzz data
        if (Size < rawSize) {
            memcpy(dataBuffer, Data, Size);
            memset((uint8_t *)dataBuffer + Size, 0, rawSize - Size);
        } else {
            memcpy(dataBuffer, Data, rawSize);
        }

        // Fuzzing API functions
        TIFFWriteRawStrip(tif, strip, dataBuffer, rawSize);
        TIFFWriteEncodedStrip(tif, strip, dataBuffer, rawSize);
        TIFFWriteRawTile(tif, 0, dataBuffer, rawSize); // Using tile 0 for testing
        TIFFWriteBufferSetup(tif, dataBuffer, rawSize);
        
        free(dataBuffer);
    }

    // Cleanup
    TIFFClose(tif);
    unlink("./dummy_file");
    return 0;
}