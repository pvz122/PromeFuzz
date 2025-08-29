// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsVEC3init at cmsmtrx.c:34:16 in lcms2_plugin.h
// _cmsVEC3init at cmsmtrx.c:34:16 in lcms2_plugin.h
// _cmsVEC3length at cmsmtrx.c:64:28 in lcms2_plugin.h
// _cmsVEC3dot at cmsmtrx.c:58:28 in lcms2_plugin.h
// _cmsVEC3distance at cmsmtrx.c:72:28 in lcms2_plugin.h
// cmsCreateXYZProfile at cmsvirt.c:606:23 in lcms2.h
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
#include <lcms2_plugin.h>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_163(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number) * 6) return 0;

    cmsFloat64Number x1 = *reinterpret_cast<const cmsFloat64Number*>(Data);
    cmsFloat64Number y1 = *reinterpret_cast<const cmsFloat64Number*>(Data + sizeof(cmsFloat64Number));
    cmsFloat64Number z1 = *reinterpret_cast<const cmsFloat64Number*>(Data + 2 * sizeof(cmsFloat64Number));
    cmsFloat64Number x2 = *reinterpret_cast<const cmsFloat64Number*>(Data + 3 * sizeof(cmsFloat64Number));
    cmsFloat64Number y2 = *reinterpret_cast<const cmsFloat64Number*>(Data + 4 * sizeof(cmsFloat64Number));
    cmsFloat64Number z2 = *reinterpret_cast<const cmsFloat64Number*>(Data + 5 * sizeof(cmsFloat64Number));

    cmsVEC3 vec1, vec2;
    _cmsVEC3init(&vec1, x1, y1, z1);
    _cmsVEC3init(&vec2, x2, y2, z2);

    _cmsVEC3length(&vec1);
    _cmsVEC3dot(&vec1, &vec2);
    _cmsVEC3distance(&vec1, &vec2);

    cmsHPROFILE profile = cmsCreateXYZProfile();
    if (profile) {
        cmsCloseProfile(profile);
    }

    return 0;
}