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

int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) return 0;

    // Fuzzing TIFFSwabArrayOfFloat
    size_t float_count = Size / sizeof(float);
    float *float_array = (float *)malloc(float_count * sizeof(float));
    memcpy(float_array, Data, float_count * sizeof(float));
    TIFFSwabArrayOfFloat(float_array, float_count);
    free(float_array);

    // Fuzzing TIFFSwabFloat
    float single_float = *(float *)Data;
    TIFFSwabFloat(&single_float);

    // Fuzzing LogLuv24fromXYZ
    if (Size >= 3 * sizeof(float)) {
        float xyz[3];
        memcpy(xyz, Data, 3 * sizeof(float));
        LogLuv24fromXYZ(xyz, 1);
    }

    // Fuzzing TIFFSwabLong
    if (Size >= sizeof(uint32_t)) {
        uint32_t long_value = *(uint32_t *)Data;
        TIFFSwabLong(&long_value);
    }

    // Fuzzing TIFFSwabArrayOfLong
    if (Size >= sizeof(uint32_t)) {
        size_t long_count = Size / sizeof(uint32_t);
        uint32_t *long_array = (uint32_t *)malloc(long_count * sizeof(uint32_t));
        memcpy(long_array, Data, long_count * sizeof(uint32_t));
        TIFFSwabArrayOfLong(long_array, long_count);
        free(long_array);
    }

    // Fuzzing LogLuv32toXYZ
    if (Size >= sizeof(uint32_t)) {
        uint32_t logluv_value = *(uint32_t *)Data;
        float xyz_output[3];
        LogLuv32toXYZ(logluv_value, xyz_output);
    }

    return 0;
}