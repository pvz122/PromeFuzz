// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// TIFFSwabFloat at tif_swab.c:165:6 in tiffio.h
// TIFFSwabArrayOfFloat at tif_swab.c:180:6 in tiffio.h
// XYZtoRGB24 at tif_luv.c:850:5 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1165:5 in tiffio.h
// LogLuv32fromXYZ at tif_luv.c:1191:5 in tiffio.h
// TIFFXYZToRGB at tif_color.c:89:6 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) return 0;

    // Test TIFFSwabArrayOfFloat
    size_t float_array_size = Size / sizeof(float);
    float *float_array = (float *)malloc(Size);
    if (float_array) {
        memcpy(float_array, Data, Size);
        TIFFSwabArrayOfFloat(float_array, float_array_size);
        free(float_array);
    }

    // Test TIFFSwabFloat
    float single_float = *(float *)Data;
    TIFFSwabFloat(&single_float);

    // Test LogLuv32fromXYZ
    if (Size >= 3 * sizeof(float)) {
        float xyz[3];
        memcpy(xyz, Data, 3 * sizeof(float));
        LogLuv32fromXYZ(xyz, 1);
    }

    // Test XYZtoRGB24
    if (Size >= 3 * sizeof(float) + 3) {
        float rgb_input[3];
        uint8_t rgb_output[3];
        memcpy(rgb_input, Data, 3 * sizeof(float));
        XYZtoRGB24(rgb_input, rgb_output);
    }

    // Test TIFFXYZToRGB
    if (Size >= sizeof(TIFFCIELabToRGB) + 3 * sizeof(float) + 3 * sizeof(uint32_t)) {
        TIFFCIELabToRGB lab_to_rgb;
        float f1 = *(float *)(Data + sizeof(TIFFCIELabToRGB));
        float f2 = *(float *)(Data + sizeof(TIFFCIELabToRGB) + sizeof(float));
        float f3 = *(float *)(Data + sizeof(TIFFCIELabToRGB) + 2 * sizeof(float));
        uint32_t r, g, b;
        TIFFXYZToRGB(&lab_to_rgb, f1, f2, f3, &r, &g, &b);
    }

    // Test LogLuv32toXYZ
    if (Size >= sizeof(uint32_t)) {
        uint32_t logluv_value = *(uint32_t *)Data;
        float xyz_output[3];
        LogLuv32toXYZ(logluv_value, xyz_output);
    }

    return 0;
}