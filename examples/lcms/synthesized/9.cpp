// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateLinearizationDeviceLinkTHR at cmsvirt.c:288:23 in lcms2.h
// cmsSetColorSpace at cmsio0.c:1087:16 in lcms2.h
// cmsSetPCS at cmsio0.c:1075:16 in lcms2.h
// cmsGetColorSpace at cmsio0.c:1081:34 in lcms2.h
// cmsGetPCS at cmsio0.c:1069:34 in lcms2.h
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
#include <lcms2.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsColorSpaceSignature) * 3) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsColorSpaceSignature colorSpace = *reinterpret_cast<const cmsColorSpaceSignature*>(Data);
    cmsColorSpaceSignature pcs = *reinterpret_cast<const cmsColorSpaceSignature*>(Data + sizeof(cmsColorSpaceSignature));
    cmsColorSpaceSignature newColorSpace = *reinterpret_cast<const cmsColorSpaceSignature*>(Data + sizeof(cmsColorSpaceSignature) * 2);

    cmsToneCurve* transferFunctions[3] = { nullptr, nullptr, nullptr };

    cmsHPROFILE profile = cmsCreateLinearizationDeviceLinkTHR(context, colorSpace, transferFunctions);
    if (profile) {
        cmsSetColorSpace(profile, newColorSpace);
        cmsSetPCS(profile, pcs);

        cmsGetColorSpace(profile);
        cmsGetPCS(profile);

        cmsCloseProfile(profile);
    }

    cmsDeleteContext(context);
    return 0;
}