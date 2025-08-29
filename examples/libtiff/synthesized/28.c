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
#include <math.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + sizeof(int)) return 0;

    // Extracting values for LogL16fromY and LogL10fromY
    double yValue = *(double *)Data;
    int intValue = *(int *)(Data + sizeof(double));

    // Fuzzing LogL16fromY
    LogL16fromY(yValue, intValue);

    // Fuzzing LogL10fromY
    LogL10fromY(yValue, intValue);

    // Prepare for LogLuv24fromXYZ
    if (Size >= sizeof(double) + sizeof(int) + sizeof(float) * 3) {
        float xyzValues[3];
        memcpy(xyzValues, Data + sizeof(double) + sizeof(int), sizeof(float) * 3);
        LogLuv24fromXYZ(xyzValues, intValue);
    }

    // Fuzzing LogL10toY
    LogL10toY(intValue);

    // Fuzzing LogL16toY
    LogL16toY(intValue);

    // Prepare for LogLuv32toXYZ
    if (Size >= sizeof(uint32_t)) {
        uint32_t logLuvValue = *(uint32_t *)Data;
        float xyzOutput[3];
        LogLuv32toXYZ(logLuvValue, xyzOutput);
    }

    return 0;
}