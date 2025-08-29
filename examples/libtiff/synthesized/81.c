// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFReadRGBAImageOriented at tif_getimage.c:610:5 in tiffio.h
// TIFFReadRGBAStrip at tif_getimage.c:3216:5 in tiffio.h
// TIFFReadRGBAStripExt at tif_getimage.c:3222:5 in tiffio.h
// TIFFRGBAImageOK at tif_getimage.c:83:5 in tiffio.h
// TIFFRGBAImageBegin at tif_getimage.c:310:5 in tiffio.h
// TIFFRGBAImageEnd at tif_getimage.c:253:6 in tiffio.h
// TIFFFdOpen at tif_unix.c:205:7 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0; // Minimum size for a valid TIFF header

    // Create a dummy TIFF file
    FILE *file = fopen("./dummy_file", "wb+");
    if (!file) return 0;

    // Write the fuzz data to the dummy TIFF file
    fwrite(Data, 1, Size, file);
    fclose(file);

    TIFF *tif = TIFFFdOpen(fileno(fopen("./dummy_file", "rb")), "./dummy_file", "r");
    if (!tif) return 0;

    char errbuf[1024];
    if (TIFFRGBAImageOK(tif, errbuf)) {
        TIFFRGBAImage img;
        if (TIFFRGBAImageBegin(&img, tif, 0, errbuf)) {
            uint32_t width = img.width;
            uint32_t height = img.height;
            uint32_t *raster = (uint32_t *)malloc(width * height * sizeof(uint32_t));
            if (raster) {
                TIFFReadRGBAImageOriented(tif, width, height, raster, 0, img.orientation);
                free(raster);
            }
            TIFFRGBAImageEnd(&img);
        }
    }

    // Test TIFFReadRGBAStrip
    uint32_t *stripRaster = (uint32_t *)malloc(1024 * sizeof(uint32_t));
    if (stripRaster) {
        TIFFReadRGBAStrip(tif, 0, stripRaster);
        free(stripRaster);
    }

    // Test TIFFReadRGBAStripExt
    if (stripRaster) {
        TIFFReadRGBAStripExt(tif, 0, stripRaster, 1);
    }

    // Cleanup
    TIFFClose(tif);
    return 0;
}