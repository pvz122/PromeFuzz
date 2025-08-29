// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabShort at tif_swab.c:33:6 in tiffio.h
// TIFFSwabArrayOfShort at tif_swab.c:81:6 in tiffio.h
// TIFFSwabArrayOfTriples at tif_swab.c:99:6 in tiffio.h
// TIFFSwabArrayOfLong at tif_swab.c:117:6 in tiffio.h
// TIFFReverseBits at tif_swab.c:310:6 in tiffio.h
// TIFFGetBitRevTable at tif_swab.c:305:22 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <tiffio.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Test TIFFSwabArrayOfShort
    uint16_t *shortArray = malloc(Size);
    if (shortArray) {
        memcpy(shortArray, Data, Size < sizeof(uint16_t) * (Size / sizeof(uint16_t)) ? Size : sizeof(uint16_t) * (Size / sizeof(uint16_t)));
        TIFFSwabArrayOfShort(shortArray, Size / sizeof(uint16_t));
        free(shortArray);
    }

    // Test TIFFSwabShort
    if (Size >= sizeof(uint16_t)) {
        uint16_t shortValue = *(uint16_t *)Data;
        TIFFSwabShort(&shortValue);
    }

    // Test TIFFSwabArrayOfLong
    uint32_t *longArray = malloc(Size);
    if (longArray) {
        memcpy(longArray, Data, Size < sizeof(uint32_t) * (Size / sizeof(uint32_t)) ? Size : sizeof(uint32_t) * (Size / sizeof(uint32_t)));
        TIFFSwabArrayOfLong(longArray, Size / sizeof(uint32_t));
        free(longArray);
    }

    // Test TIFFGetBitRevTable
    if (Size > 0) {
        int bitDepth = Data[0] % 32; // Limit bit depth to a reasonable range
        const unsigned char *bitRevTable = TIFFGetBitRevTable(bitDepth);
    }

    // Test TIFFReverseBits
    uint8_t *byteArray = malloc(Size);
    if (byteArray) {
        memcpy(byteArray, Data, Size);
        TIFFReverseBits(byteArray, Size);
        free(byteArray);
    }

    // Test TIFFSwabArrayOfTriples
    uint8_t *tripleArray = malloc(Size);
    if (tripleArray) {
        memcpy(tripleArray, Data, Size < sizeof(uint8_t) * (Size / 3) * 3 ? Size : sizeof(uint8_t) * (Size / 3) * 3);
        TIFFSwabArrayOfTriples(tripleArray, Size / 3);
        free(tripleArray);
    }

    return 0;
}