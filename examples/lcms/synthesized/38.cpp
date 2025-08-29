// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8SetDataDbl at cmscgats.c:2935:19 in lcms2.h
// cmsIT8GetDataRowColDbl at cmscgats.c:2821:28 in lcms2.h
// cmsIT8SetPropertyDbl at cmscgats.c:1538:19 in lcms2.h
// cmsIT8SetDataRowCol at cmscgats.c:2833:19 in lcms2.h
// cmsIT8SetDataRowColDbl at cmscgats.c:2843:19 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <lcms2.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHANDLE hIT8 = cmsIT8Alloc(nullptr);
    if (!hIT8) return 0;

    // Generate random data for fuzzing
    int row = *Data % 100;
    int col = (*Data + 1) % 100;
    cmsFloat64Number val = static_cast<cmsFloat64Number>(*Data) / 255.0;

    // Fuzz cmsIT8SetDataDbl
    cmsIT8SetDataDbl(hIT8, "Patch1", "Sample1", val);

    // Fuzz cmsIT8GetDataRowColDbl
    cmsIT8GetDataRowColDbl(hIT8, row, col);

    // Fuzz cmsIT8SetPropertyDbl
    cmsIT8SetPropertyDbl(hIT8, "Property1", val);

    // Fuzz cmsIT8SetDataRowCol
    char buf[16];
    snprintf(buf, sizeof(buf), "%f", val);
    cmsIT8SetDataRowCol(hIT8, row, col, buf);

    // Fuzz cmsIT8SetDataRowColDbl
    cmsIT8SetDataRowColDbl(hIT8, row, col, val);

    cmsIT8Free(hIT8);
    return 0;
}