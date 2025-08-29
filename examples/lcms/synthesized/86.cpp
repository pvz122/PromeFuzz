// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateRGBProfileTHR at cmsvirt.c:101:23 in lcms2.h
// cmsGetProfileVersion at cmsio0.c:1147:28 in lcms2.h
// cmsGetHeaderAttributes at cmsio0.c:1038:16 in lcms2.h
// cmsSetProfileVersion at cmsio0.c:1138:17 in lcms2.h
// cmsSetHeaderAttributes at cmsio0.c:1044:16 in lcms2.h
// cmsSetHeaderModel at cmsio0.c:1032:16 in lcms2.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt64Number) + sizeof(cmsFloat64Number) + sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsHPROFILE hProfile = cmsCreateRGBProfileTHR(nullptr, nullptr, nullptr, nullptr);
    if (!hProfile) {
        return 0;
    }

    cmsFloat64Number version;
    cmsUInt64Number flags;
    cmsUInt32Number model;

    memcpy(&version, Data, sizeof(cmsFloat64Number));
    memcpy(&flags, Data + sizeof(cmsFloat64Number), sizeof(cmsUInt64Number));
    memcpy(&model, Data + sizeof(cmsFloat64Number) + sizeof(cmsUInt64Number), sizeof(cmsUInt32Number));

    cmsGetProfileVersion(hProfile);
    cmsGetHeaderAttributes(hProfile, &flags);
    cmsSetProfileVersion(hProfile, version);
    cmsSetHeaderAttributes(hProfile, flags);
    cmsSetHeaderModel(hProfile, model);

    cmsCloseProfile(hProfile);
    return 0;
}