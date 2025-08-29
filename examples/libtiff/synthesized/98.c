// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFStripSize at tif_strip.c:203:10 in tiffio.h
// TIFFGetMode at tif_open.c:843:5 in tiffio.h
// TIFFReadBufferSetup at tif_read.c:1368:5 in tiffio.h
// TIFFReadScanline at tif_read.c:447:5 in tiffio.h
// TIFFReadRGBAStrip at tif_getimage.c:3216:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFReadRawStrip at tif_read.c:710:10 in tiffio.h
// TIFFReadFromUserBuffer at tif_read.c:1538:5 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (!tif) return 0;

    // Fuzzing TIFFGetMode
    int mode = TIFFGetMode(tif);

    // Fuzzing TIFFReadFromUserBuffer
    uint32_t strile = 0;
    void *inbuf = malloc(Size);
    void *outbuf = malloc(Size);
    if (inbuf && outbuf) {
        memcpy(inbuf, Data, Size);
        TIFFReadFromUserBuffer(tif, strile, inbuf, Size, outbuf, Size);
    }
    free(inbuf);
    free(outbuf);

    // Fuzzing TIFFReadRGBAStrip
    uint32_t row = 0;
    uint32_t *rgba = malloc(Size);
    if (rgba) {
        TIFFReadRGBAStrip(tif, row, rgba);
        free(rgba);
    }

    // Fuzzing TIFFReadRawStrip
    tmsize_t stripSize = TIFFStripSize(tif);
    void *rawbuf = malloc(stripSize);
    if (rawbuf) {
        TIFFReadRawStrip(tif, 0, rawbuf, stripSize);
        free(rawbuf);
    }

    // Fuzzing TIFFReadBufferSetup
    void *buffer = malloc(Size);
    if (buffer) {
        TIFFReadBufferSetup(tif, buffer, Size);
        free(buffer);
    }

    // Fuzzing TIFFReadScanline
    void *scanlineBuf = malloc(Size);
    if (scanlineBuf) {
        TIFFReadScanline(tif, scanlineBuf, row, 0);
        free(scanlineBuf);
    }

    TIFFClose(tif);
    return 0;
}