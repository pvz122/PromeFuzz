// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsGetProfileContextID at cmsio0.c:571:22 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsUnregisterPluginsTHR at cmsplugin.c:780:16 in lcms2.h
// cmsGBDAlloc at cmssm.c:302:22 in lcms2.h
// cmsGBDFree at cmssm.c:313:16 in lcms2.h
// _cmsUnlockMutex at cmserr.c:655:16 in lcms2_plugin.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
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
#include <lcms2_plugin.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(NULL, NULL);
    if (!context) return 0;

    // Test cmsGetProfileContextID
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    cmsContext profileContext = cmsGetProfileContextID(hProfile);
    cmsCloseProfile(hProfile);

    // Test cmsDupContext
    cmsContext dupContext = cmsDupContext(context, NULL);

    // Test cmsUnregisterPluginsTHR
    cmsUnregisterPluginsTHR(dupContext);

    // Test cmsGBDAlloc
    cmsHANDLE gbdHandle = cmsGBDAlloc(context);
    if (gbdHandle) {
        cmsGBDFree(gbdHandle);
    }

    // Test _cmsUnlockMutex
    void* mtx = malloc(1);
    _cmsUnlockMutex(context, mtx);
    free(mtx);

    cmsDeleteContext(dupContext);
    cmsDeleteContext(context);

    return 0;
}