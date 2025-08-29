// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFClose at tif_close.c:156:6 in tiffio.h
// TIFFIsByteSwapped at tif_open.c:884:5 in tiffio.h
// TIFFOpen at tif_unix.c:228:7 in tiffio.h
// TIFFSwabShort at tif_swab.c:33:6 in tiffio.h
// TIFFSwabArrayOfShort at tif_swab.c:81:6 in tiffio.h
// TIFFSwabArrayOfTriples at tif_swab.c:99:6 in tiffio.h
// TIFFSwabArrayOfLong at tif_swab.c:117:6 in tiffio.h
// TIFFReverseBits at tif_swab.c:310:6 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0; // Minimum size for a short swap

    // Create mutable copies of the input data
    uint8_t *reverseBitsData = (uint8_t *)malloc(Size);
    if (!reverseBitsData) return 0;
    memcpy(reverseBitsData, Data, Size);
    tmsize_t reverseBitsSize = Size;
    TIFFReverseBits(reverseBitsData, reverseBitsSize);
    free(reverseBitsData);

    // Fuzzing TIFFSwabShort
    size_t shortCount = Size / sizeof(uint16_t);
    if (shortCount > 0) {
        uint16_t *swabShortData = (uint16_t *)malloc(Size);
        if (swabShortData) {
            memcpy(swabShortData, Data, Size);
            TIFFSwabShort(swabShortData);
            free(swabShortData);
        }
    }

    // Fuzzing TIFFSwabArrayOfShort
    if (shortCount > 1) {
        uint16_t *swabArrayOfShortData = (uint16_t *)malloc(Size);
        if (swabArrayOfShortData) {
            memcpy(swabArrayOfShortData, Data, Size);
            TIFFSwabArrayOfShort(swabArrayOfShortData, shortCount);
            free(swabArrayOfShortData);
        }
    }

    // Fuzzing TIFFSwabArrayOfLong
    size_t longCount = Size / sizeof(uint32_t);
    if (longCount > 0) {
        uint32_t *swabArrayOfLongData = (uint32_t *)malloc(Size);
        if (swabArrayOfLongData) {
            memcpy(swabArrayOfLongData, Data, Size);
            TIFFSwabArrayOfLong(swabArrayOfLongData, longCount);
            free(swabArrayOfLongData);
        }
    }

    // Fuzzing TIFFSwabArrayOfTriples
    size_t tripleCount = Size / (3 * sizeof(uint8_t));
    if (tripleCount > 0) {
        uint8_t *swabArrayOfTriplesData = (uint8_t *)malloc(Size);
        if (swabArrayOfTriplesData) {
            memcpy(swabArrayOfTriplesData, Data, Size);
            TIFFSwabArrayOfTriples(swabArrayOfTriplesData, tripleCount);
            free(swabArrayOfTriplesData);
        }
    }

    // Fuzzing TIFFIsByteSwapped
    TIFF *tif = TIFFOpen("./dummy_file", "r");
    if (tif) {
        int isSwapped = TIFFIsByteSwapped(tif);
        TIFFClose(tif);
    }

    return 0;
}