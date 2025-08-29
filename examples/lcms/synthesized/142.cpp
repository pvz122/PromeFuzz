// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateTransform at cmsxform.c:1348:32 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// _cmsGetTransformUserData at cmsxform.c:758:18 in lcms2_plugin.h
// _cmsGetTransformMaxWorkers at cmsxform.c:794:26 in lcms2_plugin.h
// _cmsGetTransformFormattersFloat at cmsxform.c:772:16 in lcms2_plugin.h
// _cmsSetTransformUserData at cmsxform.c:750:16 in lcms2_plugin.h
// _cmsGetTransformWorker at cmsxform.c:787:28 in lcms2_plugin.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
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
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_142(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a dummy transform structure using cmsCreateTransform
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    cmsHTRANSFORM transform = cmsCreateTransform(hProfile, TYPE_RGB_8, hProfile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
    if (!transform) {
        cmsCloseProfile(hProfile);
        return 0;
    }

    // Test _cmsGetTransformUserData
    void *userData = _cmsGetTransformUserData((_cmstransform_struct *)transform);

    // Test _cmsGetTransformMaxWorkers
    cmsInt32Number maxWorkers = _cmsGetTransformMaxWorkers((_cmstransform_struct *)transform);

    // Test _cmsGetTransformFormattersFloat
    cmsFormatterFloat fromInput = nullptr;
    cmsFormatterFloat toOutput = nullptr;
    _cmsGetTransformFormattersFloat((_cmstransform_struct *)transform, &fromInput, &toOutput);

    // Test _cmsSetTransformUserData
    _cmsSetTransformUserData((_cmstransform_struct *)transform, nullptr, nullptr);

    // Test _cmsGetTransformWorker
    _cmsTransform2Fn worker = _cmsGetTransformWorker((_cmstransform_struct *)transform);

    cmsDeleteTransform(transform);
    cmsCloseProfile(hProfile);
    return 0;
}