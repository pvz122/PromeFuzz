// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsDesaturateLab at cmsgmt.c:515:19 in lcms2.h
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
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab) * 2) return 0;

    cmsCIELab Lab1, Lab2;
    memcpy(&Lab1, Data, sizeof(cmsCIELab));
    memcpy(&Lab2, Data + sizeof(cmsCIELab), sizeof(cmsCIELab));

    // Fuzz cmsDesaturateLab
    cmsDesaturateLab(&Lab1, 100.0, -100.0, 100.0, -100.0);

    // Fuzz cmsDeltaE
    cmsDeltaE(&Lab1, &Lab2);

    // Fuzz cmsCIE2000DeltaE
    cmsCIE2000DeltaE(&Lab1, &Lab2, 1.0, 1.0, 1.0);

    // Fuzz cmsCIE94DeltaE
    cmsCIE94DeltaE(&Lab1, &Lab2);

    // Fuzz cmsBFDdeltaE
    cmsBFDdeltaE(&Lab1, &Lab2);

    return 0;
}