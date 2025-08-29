// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabLong at tif_swab.c:45:6 in tiffio.h
// TIFFSwabFloat at tif_swab.c:165:6 in tiffio.h
// TIFFSwabArrayOfLong at tif_swab.c:117:6 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1165:5 in tiffio.h
// LogLuv24fromXYZ at tif_luv.c:1048:5 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) return 0;

    // Fuzzing TIFFSwabArrayOfFloat
    size_t floatArraySize = Size / sizeof(float);
    float *floatArray = (float *)malloc(Size);
    memcpy(floatArray, Data, Size);
    TIFFSwabArrayOfFloat(floatArray, floatArraySize);
    free(floatArray);

    // Fuzzing TIFFSwabFloat
    float singleFloat = *(float *)Data;
    TIFFSwabFloat(&singleFloat);

    // Fuzzing LogLuv24fromXYZ
    if (Size >= 3 * sizeof(float)) {
        float xyz[3];
        memcpy(xyz, Data, 3 * sizeof(float));
        LogLuv24fromXYZ(xyz, 0);
    }

    // Fuzzing TIFFSwabLong
    if (Size >= sizeof(uint32_t)) {
        uint32_t singleLong = *(uint32_t *)Data;
        TIFFSwabLong(&singleLong);
    }

    // Fuzzing TIFFSwabArrayOfLong
    size_t longArraySize = Size / sizeof(uint32_t);
    uint32_t *longArray = (uint32_t *)malloc(Size);
    memcpy(longArray, Data, Size);
    TIFFSwabArrayOfLong(longArray, longArraySize);
    free(longArray);

    // Fuzzing LogLuv32toXYZ
    if (Size >= sizeof(uint32_t)) {
        uint32_t logLuvValue = *(uint32_t *)Data;
        float xyzOutput[3];
        LogLuv32toXYZ(logLuvValue, xyzOutput);
    }

    return 0;
}