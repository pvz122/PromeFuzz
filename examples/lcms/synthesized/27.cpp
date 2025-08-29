// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateNULLProfileTHR at cmsvirt.c:950:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateProfilePlaceholder at cmsio0.c:526:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsUnregisterPluginsTHR at cmsplugin.c:780:16 in lcms2.h
// cmsGBDAlloc at cmssm.c:302:22 in lcms2.h
// cmsGBDFree at cmssm.c:313:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    // Fuzz cmsCreateNULLProfileTHR
    cmsHPROFILE nullProfile = cmsCreateNULLProfileTHR(context);
    if (nullProfile) {
        cmsCloseProfile(nullProfile);
    }

    // Fuzz cmsDupContext
    cmsContext dupContext = cmsDupContext(context, nullptr);
    if (dupContext) {
        cmsDeleteContext(dupContext);
    }

    // Fuzz cmsCreateProfilePlaceholder
    cmsHPROFILE placeholderProfile = cmsCreateProfilePlaceholder(context);
    if (placeholderProfile) {
        cmsCloseProfile(placeholderProfile);
    }

    // Fuzz cmsUnregisterPluginsTHR
    cmsUnregisterPluginsTHR(context);

    // Fuzz cmsGBDAlloc
    cmsHANDLE gbdHandle = cmsGBDAlloc(context);
    if (gbdHandle) {
        cmsGBDFree(gbdHandle);
    }

    cmsDeleteContext(context);
    return 0;
}