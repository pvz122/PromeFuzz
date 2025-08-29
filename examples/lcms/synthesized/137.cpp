// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsTempFromWhitePoint at cmswtpnt.c:143:20 in lcms2.h
// cmsXYZ2xyY at cmspcs.c:91:16 in lcms2.h
// cmsCreateLab2Profile at cmsvirt.c:513:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateLab4Profile at cmsvirt.c:559:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsWhitePointFromTemp at cmswtpnt.c:48:20 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY) + sizeof(cmsCIEXYZ) + sizeof(cmsFloat64Number)) {
        return 0;
    }

    cmsCIExyY whitePoint;
    cmsCIEXYZ xyz;
    cmsFloat64Number tempK;

    memcpy(&whitePoint, Data, sizeof(cmsCIExyY));
    memcpy(&xyz, Data + sizeof(cmsCIExyY), sizeof(cmsCIEXYZ));
    memcpy(&tempK, Data + sizeof(cmsCIExyY) + sizeof(cmsCIEXYZ), sizeof(cmsFloat64Number));

    cmsFloat64Number outputTempK;
    cmsTempFromWhitePoint(&outputTempK, &whitePoint);

    cmsCIExyY dest;
    cmsXYZ2xyY(&dest, &xyz);

    cmsHPROFILE lab2Profile = cmsCreateLab2Profile(&whitePoint);
    if (lab2Profile) {
        cmsCloseProfile(lab2Profile);
    }

    cmsHPROFILE lab4Profile = cmsCreateLab4Profile(&whitePoint);
    if (lab4Profile) {
        cmsCloseProfile(lab4Profile);
    }

    cmsWhitePointFromTemp(&whitePoint, tempK);

    return 0;
}