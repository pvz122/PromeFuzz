// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateRGBProfileTHR at cmsvirt.c:101:23 in lcms2.h
// cmsSetHeaderFlags at cmsio0.c:1002:16 in lcms2.h
// cmsSetEncodedICCversion at cmsio0.c:1111:16 in lcms2.h
// cmsGetHeaderCreator at cmsio0.c:1020:27 in lcms2.h
// cmsGetHeaderManufacturer at cmsio0.c:1008:27 in lcms2.h
// cmsGetHeaderRenderingIntent at cmsio0.c:984:27 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsHPROFILE hProfile = cmsCreateRGBProfileTHR(nullptr, nullptr, nullptr, nullptr);
    if (!hProfile) {
        return 0;
    }

    cmsUInt32Number flags = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsSetHeaderFlags(hProfile, flags);

    cmsUInt32Number version = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsSetEncodedICCversion(hProfile, version);

    cmsUInt32Number creator = cmsGetHeaderCreator(hProfile);
    cmsUInt32Number manufacturer = cmsGetHeaderManufacturer(hProfile);
    cmsUInt32Number renderingIntent = cmsGetHeaderRenderingIntent(hProfile);

    cmsCloseProfile(hProfile);

    return 0;
}