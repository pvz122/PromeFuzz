// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateTransform at cmsxform.c:1348:32 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// _cmsGetTransformUserData at cmsxform.c:758:18 in lcms2_plugin.h
// _cmsGetTransformMaxWorkers at cmsxform.c:794:26 in lcms2_plugin.h
// _cmsSetTransformUserData at cmsxform.c:750:16 in lcms2_plugin.h
// _cmsGetTransformFormatters16 at cmsxform.c:765:16 in lcms2_plugin.h
// _cmsGetTransformWorker at cmsxform.c:787:28 in lcms2_plugin.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
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
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

static void dummyFreeUserDataFn(_cmsContext_struct* ctx, void* ptr) {
    free(ptr);
}

extern "C" int LLVMFuzzerTestOneInput_129(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void*)) {
        return 0;
    }

    cmsContext ctx = cmsCreateContext(NULL, NULL);
    if (!ctx) {
        return 0;
    }

    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) {
        cmsDeleteContext(ctx);
        return 0;
    }

    cmsHTRANSFORM transform = cmsCreateTransform(hProfile, TYPE_RGB_8, hProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    if (!transform) {
        cmsCloseProfile(hProfile);
        cmsDeleteContext(ctx);
        return 0;
    }

    void *userData = _cmsGetTransformUserData((_cmstransform_struct*)transform);
    cmsInt32Number maxWorkers = _cmsGetTransformMaxWorkers((_cmstransform_struct*)transform);

    void *newUserData = malloc(1);
    _cmsSetTransformUserData((_cmstransform_struct*)transform, newUserData, dummyFreeUserDataFn);

    cmsFormatter16 fromInput, toOutput;
    _cmsGetTransformFormatters16((_cmstransform_struct*)transform, &fromInput, &toOutput);

    _cmsTransform2Fn workerFn = _cmsGetTransformWorker((_cmstransform_struct*)transform);

    cmsDeleteTransform(transform);
    cmsCloseProfile(hProfile);
    cmsDeleteContext(ctx);
    return 0;
}