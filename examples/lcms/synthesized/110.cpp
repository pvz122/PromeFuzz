// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateXYZProfileTHR at cmsvirt.c:566:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsSignalError at cmserr.c:510:16 in lcms2_plugin.h
// cmsDictAlloc at cmsnamed.c:1090:21 in lcms2.h
// cmsDictFree at cmsnamed.c:1101:16 in lcms2.h
// cmsCreateLab4ProfileTHR at cmsvirt.c:520:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsGetSupportedIntentsTHR at cmscnvrt.c:1157:27 in lcms2.h
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
#include "lcms2_plugin.h"
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_110(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    // Fuzz cmsCreateXYZProfileTHR
    cmsHPROFILE xyzProfile = cmsCreateXYZProfileTHR(context);
    if (xyzProfile) cmsCloseProfile(xyzProfile);

    // Fuzz cmsSignalError
    cmsSignalError(context, 0, "Fuzz error message");

    // Fuzz cmsDictAlloc
    cmsHANDLE dict = cmsDictAlloc(context);
    if (dict) cmsDictFree(dict);

    // Fuzz cmsCreateLab4ProfileTHR
    cmsCIExyY whitePoint = {0.3457, 0.3585, 1.0};
    cmsHPROFILE labProfile = cmsCreateLab4ProfileTHR(context, &whitePoint);
    if (labProfile) cmsCloseProfile(labProfile);

    // Fuzz cmsGetSupportedIntentsTHR
    cmsUInt32Number codes[10];
    char* descriptions[10];
    cmsGetSupportedIntentsTHR(context, 10, codes, descriptions);

    cmsDeleteContext(context);
    return 0;
}