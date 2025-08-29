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

extern void LogLuv24toXYZ(uint32_t, float *);
extern void TIFFCIELabToXYZ(TIFFCIELabToRGB *, uint32_t, int32_t, int32_t, float *, float *, float *);
extern void LogLuv32toXYZ(uint32_t, float *);
extern uint32_t LogLuv32fromXYZ(float *, int);
extern void TIFFXYZToRGB(TIFFCIELabToRGB *, float, float, float, uint32_t *, uint32_t *, uint32_t *);
extern uint32_t LogLuv24fromXYZ(float *, int);

int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return 0;

    // Fuzz LogLuv24toXYZ
    uint32_t value = *(uint32_t *)Data;
    float output[3];
    LogLuv24toXYZ(value, output);

    // Fuzz TIFFCIELabToXYZ
    TIFFCIELabToRGB labToRGB;
    float xyz[3];
    TIFFCIELabToXYZ(&labToRGB, value, 0, 0, &xyz[0], &xyz[1], &xyz[2]);

    // Fuzz LogLuv32toXYZ
    LogLuv32toXYZ(value, output);

    // Fuzz LogLuv32fromXYZ
    uint32_t result = LogLuv32fromXYZ(xyz, 0);

    // Fuzz TIFFXYZToRGB
    uint32_t r, g, b;
    TIFFXYZToRGB(&labToRGB, xyz[0], xyz[1], xyz[2], &r, &g, &b);

    // Fuzz LogLuv24fromXYZ
    uint32_t logLuvResult = LogLuv24fromXYZ(xyz, 0);

    return 0;
}