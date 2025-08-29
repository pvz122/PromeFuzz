// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateNULLProfile at cmsvirt.c:1008:23 in lcms2.h
// cmsCIECAM02Reverse at cmscam02.c:461:16 in lcms2.h
// cmsCIECAM02Forward at cmscam02.c:435:16 in lcms2.h
// cmsxyY2XYZ at cmspcs.c:102:16 in lcms2.h
// cmsLab2XYZ at cmspcs.c:161:16 in lcms2.h
// cmsFloat2XYZEncoded at cmspcs.c:374:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_70(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 3) return 0;

    double* dData = (double*)Data;

    cmsCIEXYZ xyz;
    cmsCIExyY xyY;
    cmsCIELab Lab;
    cmsJCh jch;
    cmsUInt16Number encodedXYZ[3];

    cmsHANDLE hModel = cmsCreateNULLProfile();

    // cmsCIECAM02Reverse
    jch.J = dData[0];
    jch.C = dData[1];
    jch.h = dData[2];
    cmsCIECAM02Reverse(hModel, &jch, &xyz);

    // cmsCIECAM02Forward
    xyz.X = dData[0];
    xyz.Y = dData[1];
    xyz.Z = dData[2];
    cmsCIECAM02Forward(hModel, &xyz, &jch);

    // cmsxyY2XYZ
    xyY.x = dData[0];
    xyY.y = dData[1];
    xyY.Y = dData[2];
    cmsxyY2XYZ(&xyz, &xyY);

    // cmsLab2XYZ
    Lab.L = dData[0];
    Lab.a = dData[1];
    Lab.b = dData[2];
    cmsLab2XYZ(NULL, &xyz, &Lab);

    // cmsFloat2XYZEncoded
    xyz.X = dData[0];
    xyz.Y = dData[1];
    xyz.Z = dData[2];
    cmsFloat2XYZEncoded(encodedXYZ, &xyz);

    cmsCloseProfile(hModel);

    return 0;
}