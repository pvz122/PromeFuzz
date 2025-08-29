// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCIECAM02Init at cmscam02.c:358:22 in lcms2.h
// cmsCIECAM02Reverse at cmscam02.c:461:16 in lcms2.h
// cmsCIECAM02Forward at cmscam02.c:435:16 in lcms2.h
// cmsxyY2XYZ at cmspcs.c:102:16 in lcms2.h
// cmsLab2XYZ at cmspcs.c:161:16 in lcms2.h
// cmsFloat2XYZEncoded at cmspcs.c:374:16 in lcms2.h
// cmsCIECAM02Done at cmscam02.c:427:16 in lcms2.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_98(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float) * 3) return 0;

    // Initialize structures
    cmsCIEXYZ xyz;
    cmsCIExyY xyY;
    cmsCIELab lab;
    cmsJCh jch;
    cmsUInt16Number encodedXYZ[3];

    // Populate structures with fuzzed data
    memcpy(&xyz.X, Data, sizeof(float) * 3);
    memcpy(&xyY.x, Data, sizeof(float) * 3);
    memcpy(&lab.L, Data, sizeof(float) * 3);
    memcpy(&jch.J, Data, sizeof(float) * 3);

    // Create a CIECAM02 model handle
    cmsViewingConditions vc;
    cmsHANDLE hModel = cmsCIECAM02Init(nullptr, &vc);

    // Fuzz cmsCIECAM02Reverse
    cmsCIECAM02Reverse(hModel, &jch, &xyz);

    // Fuzz cmsCIECAM02Forward
    cmsCIECAM02Forward(hModel, &xyz, &jch);

    // Fuzz cmsxyY2XYZ
    cmsxyY2XYZ(&xyz, &xyY);

    // Fuzz cmsLab2XYZ
    cmsLab2XYZ(nullptr, &xyz, &lab);

    // Fuzz cmsFloat2XYZEncoded
    cmsFloat2XYZEncoded(encodedXYZ, &xyz);

    // Cleanup
    cmsCIECAM02Done(hModel);

    return 0;
}