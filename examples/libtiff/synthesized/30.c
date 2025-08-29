// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFVStripSize at tif_strip.c:141:10 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFReadEncodedStrip at tif_read.c:527:10 in tiffio.h
// TIFFWriteEncodedStrip at tif_write.c:215:10 in tiffio.h
// TIFFWriteRawStrip at tif_write.c:328:10 in tiffio.h
// TIFFWriteEncodedTile at tif_write.c:414:10 in tiffio.h
// TIFFReverseBits at tif_swab.c:310:6 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    // Fuzzing TIFFReverseBits
    if (Size > 0) {
        uint8_t *buffer = (uint8_t *)malloc(Size);
        memcpy(buffer, Data, Size);
        TIFFReverseBits(buffer, Size);
        free(buffer);
    }

    // Fuzzing TIFFWriteRawStrip
    {
        TIFF *tif = TIFFOpen("./dummy_file", "w");
        if (tif) {
            uint32_t strip = 0;
            tmsize_t cc = Size;
            TIFFWriteRawStrip(tif, strip, (void *)Data, cc);
            TIFFClose(tif);
        }
    }

    // Fuzzing TIFFWriteEncodedTile
    {
        TIFF *tif = TIFFOpen("./dummy_file", "w");
        if (tif) {
            uint32_t tile = 0;
            tmsize_t cc = Size;
            TIFFWriteEncodedTile(tif, tile, (void *)Data, cc);
            TIFFClose(tif);
        }
    }

    // Fuzzing TIFFWriteEncodedStrip
    {
        TIFF *tif = TIFFOpen("./dummy_file", "w");
        if (tif) {
            uint32_t strip = 0;
            tmsize_t cc = Size;
            TIFFWriteEncodedStrip(tif, strip, (void *)Data, cc);
            TIFFClose(tif);
        }
    }

    // Fuzzing TIFFReadEncodedStrip
    {
        TIFF *tif = TIFFOpen("./dummy_file", "r");
        if (tif) {
            uint32_t strip = 0;
            uint8_t *buf = (uint8_t *)malloc(Size);
            tmsize_t cc = TIFFReadEncodedStrip(tif, strip, buf, Size);
            free(buf);
            TIFFClose(tif);
        }
    }

    // Fuzzing TIFFVStripSize
    {
        TIFF *tif = TIFFOpen("./dummy_file", "r");
        if (tif) {
            uint32_t nrows = Size;
            TIFFVStripSize(tif, nrows);
            TIFFClose(tif);
        }
    }

    return 0;
}