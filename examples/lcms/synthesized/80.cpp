// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCIECAM02Init at cmscam02.c:358:22 in lcms2.h
// cmsCIECAM02Reverse at cmscam02.c:461:16 in lcms2.h
// cmsCIECAM02Forward at cmscam02.c:435:16 in lcms2.h
// cmsCIECAM02Done at cmscam02.c:427:16 in lcms2.h
// cmsxyY2XYZ at cmspcs.c:102:16 in lcms2.h
// cmsLab2XYZ at cmspcs.c:161:16 in lcms2.h
// cmsFloat2XYZEncoded at cmspcs.c:374:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ) + sizeof(cmsJCh) + sizeof(cmsCIExyY) + sizeof(cmsCIELab)) {
        return 0;
    }

    cmsCIEXYZ xyz;
    cmsJCh jch;
    cmsCIExyY xyY;
    cmsCIELab lab;

    memcpy(&xyz, Data, sizeof(cmsCIEXYZ));
    memcpy(&jch, Data + sizeof(cmsCIEXYZ), sizeof(cmsJCh));
    memcpy(&xyY, Data + sizeof(cmsCIEXYZ) + sizeof(cmsJCh), sizeof(cmsCIExyY));
    memcpy(&lab, Data + sizeof(cmsCIEXYZ) + sizeof(cmsJCh) + sizeof(cmsCIExyY), sizeof(cmsCIELab));

    cmsViewingConditions vc = { 0 };
    cmsHANDLE hModel = cmsCIECAM02Init(NULL, &vc);
    if (hModel) {
        cmsCIECAM02Reverse(hModel, &jch, &xyz);
        cmsCIECAM02Forward(hModel, &xyz, &jch);
        cmsCIECAM02Done(hModel);
    }

    cmsxyY2XYZ(&xyz, &xyY);
    cmsLab2XYZ(NULL, &xyz, &lab);

    cmsUInt16Number XYZEncoded[3];
    cmsFloat2XYZEncoded(XYZEncoded, &xyz);

    return 0;
}