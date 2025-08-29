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
#include <stdint.h>
#include <stdlib.h>
#include <tiffio.h>

extern int uv_decode(double *, double *, int);
extern int uv_encode(double, double, int);
extern double LogL10toY(int);
extern int LogL10fromY(double, int);
extern double LogL16toY(int);
extern int LogL16fromY(double, int);

int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 2 + sizeof(int)) return 0;

    double uv1 = *(double *)(Data);
    double uv2 = *(double *)(Data + sizeof(double));
    int intVal = *(int *)(Data + sizeof(double) * 2);

    // Fuzz uv_decode
    double output1[2];
    uv_decode(output1, &uv2, intVal);

    // Fuzz uv_encode
    int encoded = uv_encode(uv1, uv2, intVal);

    // Fuzz LogL10toY
    double logToY = LogL10toY(intVal);

    // Fuzz LogL10fromY
    int logFromY = LogL10fromY(logToY, intVal);

    // Fuzz LogL16toY
    double log16ToY = LogL16toY(intVal);

    // Fuzz LogL16fromY
    int log16FromY = LogL16fromY(log16ToY, intVal);

    return 0;
}