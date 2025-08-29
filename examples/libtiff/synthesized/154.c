// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFRawStripSize64 at tif_strip.c:152:10 in tiffio.h
// TIFFVStripSize64 at tif_strip.c:87:10 in tiffio.h
// TIFFDefaultStripSize at tif_strip.c:217:10 in tiffio.h
// TIFFCurrentStrip at tif_open.c:874:10 in tiffio.h
// TIFFSetField at tif_dir.c:1146:5 in tiffio.h
// TIFFWriteScanline at tif_write.c:47:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFComputeStrip at tif_strip.c:35:10 in tiffio.h
// TIFFNumberOfStrips at tif_strip.c:64:10 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_154(const uint8_t *Data, size_t Size) {
    // Initialize TIFF structure
    TIFF *tif = TIFFOpen("./dummy_file", "w+");
    if (!tif) return 0;

    // Prepare a dummy TIFF file with random data
    uint32_t width = 100;
    uint32_t height = 100;
    TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField(tif, TIFFTAG_IMAGELENGTH, height);
    TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 3);
    TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

    // Allocate buffer for a single scanline
    size_t scanline_size = width * 3; // Assuming 3 bytes per pixel
    uint8_t *buf = (uint8_t *)malloc(scanline_size);
    if (!buf) {
        TIFFClose(tif);
        return 0;
    }

    // Write random data into the TIFF file
    for (uint32_t row = 0; row < height; row++) {
        // Ensure we do not exceed the input data size
        size_t copy_size = (Size < scanline_size) ? Size : scanline_size;
        memcpy(buf, Data, copy_size);
        TIFFWriteScanline(tif, buf, row, 0);
    }

    // Test various TIFF functions
    TIFFCurrentStrip(tif);
    TIFFDefaultStripSize(tif, 0);
    TIFFVStripSize64(tif, 10); // Use a small number of rows
    TIFFNumberOfStrips(tif);
    TIFFComputeStrip(tif, 0, 0); // Use a small row index
    TIFFRawStripSize64(tif, 0); // Check the first strip size

    // Cleanup
    free(buf);
    TIFFClose(tif);
    return 0;
}