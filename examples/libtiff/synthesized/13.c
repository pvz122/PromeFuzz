// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
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
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) return 0;

    // Prepare a buffer for reading/writing tiles
    uint32_t *rgba_buffer = (uint32_t *)malloc(256 * sizeof(uint32_t));
    if (!rgba_buffer) {
        TIFFClose(tif);
        return 0;
    }

    // Invoke the target functions with random parameters
    uint32_t x = Data[0] % 1024; // Random x coordinate
    uint32_t y = Data[1] % 1024; // Random y coordinate
    uint32_t z = 0; // z coordinate
    uint16_t s = 0; // sample index

    // Test TIFFComputeTile
    TIFFComputeTile(tif, x, y, z, s);

    // Test TIFFNumberOfTiles
    TIFFNumberOfTiles(tif);

    // Test TIFFReadRGBATile
    TIFFReadRGBATile(tif, x, y, rgba_buffer);

    // Test TIFFReadTile
    TIFFReadTile(tif, rgba_buffer, x, y, z, s);

    // Test TIFFWriteTile
    TIFFWriteTile(tif, rgba_buffer, x, y, z, s);

    // Test TIFFCheckTile
    TIFFCheckTile(tif, x, y, z, s);

    // Cleanup
    free(rgba_buffer);
    TIFFClose(tif);

    return 0;
}