// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsGetProfileVersion at cmsio0.c:1147:28 in lcms2.h
// cmsSetHeaderRenderingIntent at cmsio0.c:990:16 in lcms2.h
// cmsSetProfileVersion at cmsio0.c:1138:17 in lcms2.h
// cmsGetHeaderFlags at cmsio0.c:996:27 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_87(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    // Create a dummy ICC profile
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return 0;

    // Fuzz cmsGetProfileVersion
    cmsFloat64Number version = cmsGetProfileVersion(hProfile);

    // Fuzz cmsSetHeaderRenderingIntent
    cmsUInt32Number renderingIntent = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsSetHeaderRenderingIntent(hProfile, renderingIntent);

    // Fuzz cmsSetProfileVersion
    cmsFloat64Number newVersion = static_cast<cmsFloat64Number>(renderingIntent) / 100.0;
    cmsSetProfileVersion(hProfile, newVersion);

    // Fuzz cmsGetHeaderFlags
    cmsUInt32Number flags = cmsGetHeaderFlags(hProfile);

    // Fuzz cmsSetHeaderModel
    cmsUInt32Number model = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsSetHeaderModel(hProfile, model);

    // Cleanup
    cmsCloseProfile(hProfile);

    return 0;
}