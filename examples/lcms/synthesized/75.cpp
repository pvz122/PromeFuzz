// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateXYZProfileTHR at cmsvirt.c:566:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreate_OkLabProfile at cmsvirt.c:679:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateProfilePlaceholder at cmsio0.c:526:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsGBDAlloc at cmssm.c:302:22 in lcms2.h
// cmsGBDFree at cmssm.c:313:16 in lcms2.h
// cmsCreateLab4ProfileTHR at cmsvirt.c:520:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "lcms2.h"
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext ctx = cmsCreateContext(nullptr, nullptr);
    if (!ctx) return 0;

    switch (Data[0] % 5) {
        case 0: {
            cmsHPROFILE profile = cmsCreateXYZProfileTHR(ctx);
            if (profile) cmsCloseProfile(profile);
            break;
        }
        case 1: {
            cmsHPROFILE profile = cmsCreate_OkLabProfile(ctx);
            if (profile) cmsCloseProfile(profile);
            break;
        }
        case 2: {
            cmsHPROFILE profile = cmsCreateProfilePlaceholder(ctx);
            if (profile) cmsCloseProfile(profile);
            break;
        }
        case 3: {
            cmsHANDLE handle = cmsGBDAlloc(ctx);
            if (handle) cmsGBDFree(handle);
            break;
        }
        case 4: {
            cmsCIExyY whitePoint = {0.3457, 0.3585, 1.0}; // Example white point
            cmsHPROFILE profile = cmsCreateLab4ProfileTHR(ctx, &whitePoint);
            if (profile) cmsCloseProfile(profile);
            break;
        }
    }

    cmsDeleteContext(ctx);
    return 0;
}