// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogLuv24toXYZ at tif_luv.c:1017:5 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1165:5 in tiffio.h
// LogLuv24fromXYZ at tif_luv.c:1048:5 in tiffio.h
// LogLuv32fromXYZ at tif_luv.c:1191:5 in tiffio.h
// TIFFCIELabToXYZ at tif_color.c:43:6 in tiffio.h
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

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float) * 3) return 0;

    // Prepare data for LogLuv24fromXYZ and LogLuv32fromXYZ
    float xyz[3];
    memcpy(xyz, Data, sizeof(float) * 3);

    // Fuzz LogLuv24fromXYZ
    uint32_t logluv24 = LogLuv24fromXYZ(xyz, 1);

    // Fuzz LogLuv32fromXYZ
    uint32_t logluv32 = LogLuv32fromXYZ(xyz, 1);

    // Prepare data for TIFFXYZToRGB and TIFFCIELabToXYZ
    TIFFCIELabToRGB labToRGB;
    uint32_t r, g, b;
    TIFFXYZToRGB(&labToRGB, xyz[0], xyz[1], xyz[2], &r, &g, &b);

    // Fuzz LogLuv24toXYZ
    float xyzOutput24[3];
    LogLuv24toXYZ(logluv24, xyzOutput24);

    // Fuzz LogLuv32toXYZ
    float xyzOutput32[3];
    LogLuv32toXYZ(logluv32, xyzOutput32);

    // Fuzz TIFFCIELabToXYZ
    int32_t lab1 = 0, lab2 = 0;
    TIFFCIELabToXYZ(&labToRGB, logluv24, lab1, lab2, &xyzOutput24[0], &xyzOutput24[1], &xyzOutput24[2]);

    return 0;
}