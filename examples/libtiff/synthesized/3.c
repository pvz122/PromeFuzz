// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFTileSize at tif_tile.c:253:10 in tiffio.h
// TIFFReadRGBATile at tif_getimage.c:3291:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFComputeTile at tif_tile.c:35:10 in tiffio.h
// TIFFCheckTile at tif_tile.c:71:5 in tiffio.h
// TIFFNumberOfTiles at tif_tile.c:108:10 in tiffio.h
// TIFFReadTile at tif_read.c:933:10 in tiffio.h
// TIFFWriteTile at tif_write.c:387:10 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    // Initialize TIFF pointer
    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) return 0;

    // Prepare a buffer for tile data
    uint32_t x = 0, y = 0, z = 0;
    uint16_t sample = 0;
    tmsize_t tileSize = TIFFTileSize(tif);
    void *buf = malloc(tileSize);
    if (buf == NULL) {
        TIFFClose(tif);
        return 0;
    }

    // Fill the buffer with fuzz data
    if (Size < tileSize) {
        memcpy(buf, Data, Size);
    } else {
        memcpy(buf, Data, tileSize);
    }

    // Invoke target functions
    uint32_t numTiles = TIFFNumberOfTiles(tif);
    tmsize_t writtenSize = TIFFWriteTile(tif, buf, x, y, z, sample);
    tmsize_t readSize = TIFFReadTile(tif, buf, x, y, z, sample);
    uint32_t tileIndex = TIFFComputeTile(tif, x, y, z, sample);
    int checkTile = TIFFCheckTile(tif, x, y, z, sample);
    int readRGBA = TIFFReadRGBATile(tif, x, y, (uint32_t *)buf);

    // Cleanup
    free(buf);
    TIFFClose(tif);
    
    return 0;
}