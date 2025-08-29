// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogL16toY at tif_luv.c:786:5 in tiffio.h
// LogL10toY at tif_luv.c:868:5 in tiffio.h
// LogLuv32toXYZ at tif_luv.c:1165:5 in tiffio.h
// LogL16fromY at tif_luv.c:801:5 in tiffio.h
// LogL10fromY at tif_luv.c:879:5 in tiffio.h
// LogLuv24fromXYZ at tif_luv.c:1048:5 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <tiffio.h>

extern int LogL16fromY(double, int);
extern int LogL10fromY(double, int);
extern uint32_t LogLuv24fromXYZ(float *, int);
extern double LogL10toY(int);
extern double LogL16toY(int);
extern void LogLuv32toXYZ(uint32_t, float *);

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 52) return 0; // Ensure we have enough data for all operations

    // Fuzzing LogL16fromY
    double y1 = *(double *)Data;
    int int1 = *(int *)(Data + 8);
    LogL16fromY(y1, int1);

    // Fuzzing LogL10fromY
    double y2 = *(double *)Data;
    int int2 = *(int *)(Data + 16);
    LogL10fromY(y2, int2);

    // Fuzzing LogLuv24fromXYZ
    float xyz[3];
    memcpy(xyz, Data + 24, sizeof(float) * 3);
    int int3 = *(int *)(Data + 36);
    LogLuv24fromXYZ(xyz, int3);

    // Fuzzing LogL10toY
    int int4 = *(int *)(Data + 40);
    LogL10toY(int4);

    // Fuzzing LogL16toY
    int int5 = *(int *)(Data + 44);
    LogL16toY(int5);

    // Fuzzing LogLuv32toXYZ
    uint32_t uint32 = *(uint32_t *)(Data + 48);
    float output[3];
    LogLuv32toXYZ(uint32, output);

    return 0;
}