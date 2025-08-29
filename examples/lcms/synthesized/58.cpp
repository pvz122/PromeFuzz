// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCMCdeltaE at cmspcs.c:548:28 in lcms2.h
// cmsDeltaE at cmspcs.c:438:28 in lcms2.h
// cmsCIE2000DeltaE at cmspcs.c:589:28 in lcms2.h
// cmsCIE94DeltaE at cmspcs.c:451:28 in lcms2.h
// cmsBFDdeltaE at cmspcs.c:497:28 in lcms2.h
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
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab) * 2 + sizeof(cmsFloat64Number) * 5) return 0;

    const cmsCIELab* Lab1 = reinterpret_cast<const cmsCIELab*>(Data);
    const cmsCIELab* Lab2 = reinterpret_cast<const cmsCIELab*>(Data + sizeof(cmsCIELab));
    const cmsFloat64Number* params = reinterpret_cast<const cmsFloat64Number*>(Data + sizeof(cmsCIELab) * 2);

    cmsCMCdeltaE(Lab1, Lab2, params[0], params[1]);
    cmsDeltaE(Lab1, Lab2);
    cmsCIE2000DeltaE(Lab1, Lab2, params[2], params[3], params[4]);
    cmsCIE94DeltaE(Lab1, Lab2);
    cmsBFDdeltaE(Lab1, Lab2);

    return 0;
}