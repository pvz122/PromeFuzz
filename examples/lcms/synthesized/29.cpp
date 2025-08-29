// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateNULLProfileTHR at cmsvirt.c:950:23 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsGetProfileContextID at cmsio0.c:571:22 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateProfilePlaceholder at cmsio0.c:526:23 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsGBDAlloc at cmssm.c:302:22 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsGBDFree at cmssm.c:313:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsHPROFILE hProfile = cmsCreateNULLProfileTHR(context);
    if (!hProfile) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsContext contextID = cmsGetProfileContextID(hProfile);
    if (!contextID) {
        cmsCloseProfile(hProfile);
        cmsDeleteContext(context);
        return 0;
    }

    cmsContext dupContext = cmsDupContext(contextID, nullptr);
    if (!dupContext) {
        cmsCloseProfile(hProfile);
        cmsDeleteContext(context);
        return 0;
    }

    cmsHPROFILE placeholderProfile = cmsCreateProfilePlaceholder(dupContext);
    if (!placeholderProfile) {
        cmsDeleteContext(dupContext);
        cmsCloseProfile(hProfile);
        cmsDeleteContext(context);
        return 0;
    }

    cmsHANDLE gbdHandle = cmsGBDAlloc(dupContext);
    if (!gbdHandle) {
        cmsCloseProfile(placeholderProfile);
        cmsDeleteContext(dupContext);
        cmsCloseProfile(hProfile);
        cmsDeleteContext(context);
        return 0;
    }

    cmsCloseProfile(placeholderProfile);
    cmsGBDFree(gbdHandle);
    cmsDeleteContext(dupContext);
    cmsCloseProfile(hProfile);
    cmsDeleteContext(context);

    return 0;
}