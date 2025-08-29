// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsXYZ2xyY at cmspcs.c:91:16 in lcms2.h
// cmsD50_XYZ at cmswtpnt.c:31:28 in lcms2.h
// cmsXYZ2Lab at cmspcs.c:143:16 in lcms2.h
// cmsLab2XYZ at cmspcs.c:161:16 in lcms2.h
// cmsAdaptToIlluminant at cmswtpnt.c:328:19 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_82(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ) * 3 + sizeof(cmsCIELab) + sizeof(cmsCIExyY)) {
        return 0;
    }

    const cmsCIEXYZ* xyz1 = reinterpret_cast<const cmsCIEXYZ*>(Data);
    const cmsCIEXYZ* xyz2 = reinterpret_cast<const cmsCIEXYZ*>(Data + sizeof(cmsCIEXYZ));
    const cmsCIEXYZ* xyz3 = reinterpret_cast<const cmsCIEXYZ*>(Data + sizeof(cmsCIEXYZ) * 2);
    const cmsCIELab* lab = reinterpret_cast<const cmsCIELab*>(Data + sizeof(cmsCIEXYZ) * 3);
    const cmsCIExyY* xyY = reinterpret_cast<const cmsCIExyY*>(Data + sizeof(cmsCIEXYZ) * 3 + sizeof(cmsCIELab));

    cmsCIExyY dest_xyY;
    cmsCIELab dest_lab;
    cmsCIEXYZ dest_xyz;
    cmsBool result;

    // Test cmsXYZ2xyY
    cmsXYZ2xyY(&dest_xyY, xyz1);

    // Test cmsD50_XYZ
    const cmsCIEXYZ* d50 = cmsD50_XYZ();

    // Test cmsXYZ2Lab
    cmsXYZ2Lab(d50, &dest_lab, xyz2);

    // Test cmsLab2XYZ
    cmsLab2XYZ(d50, &dest_xyz, lab);

    // Test cmsAdaptToIlluminant
    result = cmsAdaptToIlluminant(&dest_xyz, xyz1, xyz3, xyz2);

    return 0;
}