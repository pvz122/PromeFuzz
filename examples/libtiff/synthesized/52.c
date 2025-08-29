// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabDouble at tif_swab.c:201:6 in tiffio.h
// TIFFSwabArrayOfShort at tif_swab.c:81:6 in tiffio.h
// TIFFSwabArrayOfTriples at tif_swab.c:99:6 in tiffio.h
// TIFFSwabArrayOfLong at tif_swab.c:117:6 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
// TIFFSwabArrayOfDouble at tif_swab.c:222:6 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "tiffio.h"

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzzing TIFFSwabArrayOfFloat
    size_t floatCount = Size / sizeof(float);
    float *floatArray = (float *)malloc(Size);
    if (floatArray) {
        memcpy(floatArray, Data, Size);
        TIFFSwabArrayOfFloat(floatArray, floatCount);
        free(floatArray);
    }

    // Fuzzing TIFFSwabArrayOfDouble
    size_t doubleCount = Size / sizeof(double);
    double *doubleArray = (double *)malloc(Size);
    if (doubleArray) {
        memcpy(doubleArray, Data, Size);
        TIFFSwabArrayOfDouble(doubleArray, doubleCount);
        free(doubleArray);
    }

    // Fuzzing TIFFSwabArrayOfShort
    size_t shortCount = Size / sizeof(uint16_t);
    uint16_t *shortArray = (uint16_t *)malloc(Size);
    if (shortArray) {
        memcpy(shortArray, Data, Size);
        TIFFSwabArrayOfShort(shortArray, shortCount);
        free(shortArray);
    }

    // Fuzzing TIFFSwabArrayOfTriples
    size_t tripleCount = Size / (3 * sizeof(uint8_t));
    uint8_t *tripleArray = (uint8_t *)malloc(Size);
    if (tripleArray) {
        memcpy(tripleArray, Data, Size);
        TIFFSwabArrayOfTriples(tripleArray, tripleCount);
        free(tripleArray);
    }

    // Fuzzing TIFFSwabDouble
    if (Size >= sizeof(double)) {
        double *singleDouble = (double *)malloc(sizeof(double));
        if (singleDouble) {
            memcpy(singleDouble, Data, sizeof(double));
            TIFFSwabDouble(singleDouble);
            free(singleDouble);
        }
    }

    // Fuzzing TIFFSwabArrayOfLong
    size_t longCount = Size / sizeof(uint32_t);
    uint32_t *longArray = (uint32_t *)malloc(Size);
    if (longArray) {
        memcpy(longArray, Data, Size);
        TIFFSwabArrayOfLong(longArray, longCount);
        free(longArray);
    }

    return 0;
}