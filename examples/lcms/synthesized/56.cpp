// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsLCh2Lab at cmspcs.c:358:16 in lcms2.h
// cmsLCh2Lab at cmspcs.c:358:16 in lcms2.h
// cmsCMCdeltaE at cmspcs.c:548:28 in lcms2.h
// cmsDeltaE at cmspcs.c:438:28 in lcms2.h
// cmsCIE94DeltaE at cmspcs.c:451:28 in lcms2.h
// cmsLab2LCh at cmspcs.c:349:16 in lcms2.h
// cmsLab2LCh at cmspcs.c:349:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_56(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab) * 2 + sizeof(cmsCIELCh) * 2 + sizeof(cmsFloat64Number) * 2) {
        return 0;
    }

    cmsCIELab lab1, lab2;
    cmsCIELCh lch1, lch2;
    cmsFloat64Number l, c;

    memcpy(&lab1, Data, sizeof(cmsCIELab));
    memcpy(&lab2, Data + sizeof(cmsCIELab), sizeof(cmsCIELab));
    memcpy(&lch1, Data + sizeof(cmsCIELab) * 2, sizeof(cmsCIELCh));
    memcpy(&lch2, Data + sizeof(cmsCIELab) * 2 + sizeof(cmsCIELCh), sizeof(cmsCIELCh));
    memcpy(&l, Data + sizeof(cmsCIELab) * 2 + sizeof(cmsCIELCh) * 2, sizeof(cmsFloat64Number));
    memcpy(&c, Data + sizeof(cmsCIELab) * 2 + sizeof(cmsCIELCh) * 2 + sizeof(cmsFloat64Number), sizeof(cmsFloat64Number));

    cmsLCh2Lab(&lab1, &lch1);
    cmsLCh2Lab(&lab2, &lch2);

    cmsCMCdeltaE(&lab1, &lab2, l, c);
    cmsDeltaE(&lab1, &lab2);
    cmsCIE94DeltaE(&lab1, &lab2);

    cmsLab2LCh(&lch1, &lab1);
    cmsLab2LCh(&lch2, &lab2);

    return 0;
}