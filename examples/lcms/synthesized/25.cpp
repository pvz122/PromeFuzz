// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsMD5computeID at cmsmd5.c:257:19 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsMD5alloc at cmsmd5.c:154:21 in lcms2_plugin.h
// cmsMD5finish at cmsmd5.c:215:16 in lcms2_plugin.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateTransformTHR at cmsxform.c:1331:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsSetDeviceClass at cmsio0.c:1099:16 in lcms2.h
// cmsIsIntentSupported at cmsio1.c:864:20 in lcms2.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy profile
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return 0;

    // Fuzz cmsMD5computeID
    cmsMD5computeID(hProfile);

    // Fuzz cmsMD5finish
    cmsProfileID ProfileID;
    cmsContext ContextID = cmsCreateContext(nullptr, nullptr);
    cmsHANDLE Handle = cmsMD5alloc(ContextID);
    if (Handle) {
        cmsMD5finish(&ProfileID, Handle);
        // Do not call _cmsFree here, as cmsMD5finish already frees the handle
    }
    cmsDeleteContext(ContextID);

    // Fuzz cmsCreateTransformTHR
    ContextID = cmsCreateContext(nullptr, nullptr);
    cmsHTRANSFORM hTransform = cmsCreateTransformTHR(ContextID, hProfile, TYPE_RGB_8, hProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    if (hTransform) {
        cmsDeleteTransform(hTransform);
    }
    cmsDeleteContext(ContextID);

    // Fuzz cmsSetDeviceClass
    cmsSetDeviceClass(hProfile, cmsSigInputClass);

    // Fuzz cmsIsIntentSupported
    cmsIsIntentSupported(hProfile, INTENT_PERCEPTUAL, 0);

    // Cleanup
    cmsCloseProfile(hProfile);

    return 0;
}