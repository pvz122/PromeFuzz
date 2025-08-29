// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsXYZ2xyY at cmspcs.c:91:16 in lcms2.h
// cmsxyY2XYZ at cmspcs.c:102:16 in lcms2.h
// cmsCreateLab2Profile at cmsvirt.c:513:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateLab4Profile at cmsvirt.c:559:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsD50_xyY at cmswtpnt.c:38:28 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ) + sizeof(cmsCIExyY)) return 0;

    cmsCIEXYZ xyz;
    cmsCIExyY xyY;

    memcpy(&xyz, Data, sizeof(cmsCIEXYZ));
    memcpy(&xyY, Data + sizeof(cmsCIEXYZ), sizeof(cmsCIExyY));

    cmsXYZ2xyY(&xyY, &xyz);
    cmsxyY2XYZ(&xyz, &xyY);

    cmsHPROFILE lab2Profile = cmsCreateLab2Profile(&xyY);
    if (lab2Profile) cmsCloseProfile(lab2Profile);

    cmsHPROFILE lab4Profile = cmsCreateLab4Profile(&xyY);
    if (lab4Profile) cmsCloseProfile(lab4Profile);

    const cmsCIExyY* d50 = cmsD50_xyY();
    (void)d50;

    return 0;
}