// This fuzz driver is generated for library libtiff, aiming to fuzz the following functions:
// LogL16toY at tif_luv.c:786:5 in tiffio.h
// LogL10toY at tif_luv.c:868:5 in tiffio.h
// uv_decode at tif_luv.c:982:5 in tiffio.h
// LogL16fromY at tif_luv.c:801:5 in tiffio.h
// LogL10fromY at tif_luv.c:879:5 in tiffio.h
// uv_encode at tif_luv.c:952:5 in tiffio.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiffio.h>

int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 3 + sizeof(int)) return 0;

    double value1 = *(double *)Data;
    int value2 = *(int *)(Data + sizeof(double));

    // Fuzz LogL16fromY
    LogL16fromY(value1, value2);

    // Fuzz LogL10fromY
    LogL10fromY(value1, value2);

    // Fuzz LogL10toY
    LogL10toY(value2);

    // Fuzz LogL16toY
    LogL16toY(value2);

    // Prepare buffers for uv_decode and uv_encode
    double uv1 = *(double *)(Data + sizeof(double) + sizeof(int));
    double uv2 = *(double *)(Data + sizeof(double) + sizeof(int) + sizeof(double));

    // Fuzz uv_decode
    uv_decode(&uv1, &uv2, value2);

    // Fuzz uv_encode
    uv_encode(uv1, uv2, value2);

    return 0;
}