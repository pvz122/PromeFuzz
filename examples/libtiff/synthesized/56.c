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
#include <tiffio.h>

int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzzing TIFFReverseBits
    uint8_t *bitArray = malloc(Size);
    if (bitArray) {
        memcpy(bitArray, Data, Size);
        TIFFReverseBits(bitArray, Size);
        free(bitArray);
    }

    // Fuzzing TIFFSwabShort
    if (Size >= sizeof(uint16_t)) {
        uint16_t *shortArray = malloc(Size);
        if (shortArray) {
            memcpy(shortArray, Data, Size);
            TIFFSwabShort(shortArray);
            free(shortArray);
        }
    }

    // Fuzzing TIFFSwabArrayOfShort
    if (Size >= sizeof(uint16_t) * 2) {
        uint16_t *shortArray = malloc(Size);
        if (shortArray) {
            memcpy(shortArray, Data, Size);
            TIFFSwabArrayOfShort(shortArray, Size / sizeof(uint16_t));
            free(shortArray);
        }
    }

    // Fuzzing TIFFSwabArrayOfTriples
    if (Size >= sizeof(uint8_t) * 3) {
        uint8_t *tripleArray = malloc(Size);
        if (tripleArray) {
            memcpy(tripleArray, Data, Size);
            TIFFSwabArrayOfTriples(tripleArray, Size / 3);
            free(tripleArray);
        }
    }

    // Fuzzing TIFFSwabArrayOfLong
    if (Size >= sizeof(uint32_t)) {
        uint32_t *longArray = malloc(Size);
        if (longArray) {
            memcpy(longArray, Data, Size);
            TIFFSwabArrayOfLong(longArray, Size / sizeof(uint32_t));
            free(longArray);
        }
    }

    // Fuzzing TIFFIsByteSwapped
    // Create a dummy TIFF file to avoid AddressSanitizer error
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
        
        TIFF *tif = TIFFOpen("./dummy_file", "r");
        if (tif) {
            TIFFIsByteSwapped(tif);
            TIFFClose(tif);
        }
    }

    return 0;
}