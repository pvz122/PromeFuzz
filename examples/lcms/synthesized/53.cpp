// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfileTHR at cmsvirt.c:642:23 in lcms2.h
// cmsCreateMultiprofileTransformTHR at cmsxform.c:1279:25 in lcms2.h
// cmsCreateBCHSWabstractProfileTHR at cmsvirt.c:850:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateTransformTHR at cmsxform.c:1331:25 in lcms2.h
// cmsTransform2DeviceLink at cmsvirt.c:1184:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDoTransform at cmsxform.c:192:16 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
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
#include <lcms2.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    // Create dummy profiles
    cmsHPROFILE profiles[255];
    for (int i = 0; i < 255; ++i) {
        profiles[i] = cmsCreate_sRGBProfileTHR(context);
    }

    // Fuzz cmsCreateMultiprofileTransformTHR
    cmsUInt32Number nProfiles = (Data[0] % 254) + 1;
    cmsUInt32Number inputFormat = TYPE_RGB_8;
    cmsUInt32Number outputFormat = TYPE_RGB_8;
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;
    cmsHTRANSFORM transform = cmsCreateMultiprofileTransformTHR(context, profiles, nProfiles, inputFormat, outputFormat, intent, flags);

    // Fuzz cmsCreateBCHSWabstractProfileTHR
    cmsUInt32Number nLUTPoints = 256;
    cmsFloat64Number bright = static_cast<cmsFloat64Number>(Data[1]) / 255.0;
    cmsFloat64Number contrast = static_cast<cmsFloat64Number>(Data[2]) / 255.0;
    cmsFloat64Number hue = static_cast<cmsFloat64Number>(Data[3]) / 255.0;
    cmsFloat64Number saturation = static_cast<cmsFloat64Number>(Data[4]) / 255.0;
    cmsUInt32Number tempSrc = 5000;
    cmsUInt32Number tempDest = 6500;
    cmsHPROFILE bchswProfile = cmsCreateBCHSWabstractProfileTHR(context, nLUTPoints, bright, contrast, hue, saturation, tempSrc, tempDest);
    if (bchswProfile) cmsCloseProfile(bchswProfile);

    // Fuzz cmsCreateTransformTHR
    cmsHTRANSFORM simpleTransform = cmsCreateTransformTHR(context, profiles[0], inputFormat, profiles[1], outputFormat, intent, flags);

    // Fuzz cmsTransform2DeviceLink
    if (transform) {
        cmsHPROFILE deviceLink = cmsTransform2DeviceLink(transform, 4.0, flags);
        if (deviceLink) cmsCloseProfile(deviceLink);
    }

    // Fuzz cmsDoTransform
    if (simpleTransform) {
        uint8_t inputBuffer[3] = {Data[5], Data[6], Data[7]};
        uint8_t outputBuffer[3];
        cmsDoTransform(simpleTransform, inputBuffer, outputBuffer, 1);
    }

    // Cleanup
    if (transform) cmsDeleteTransform(transform);
    if (simpleTransform) cmsDeleteTransform(simpleTransform);
    for (int i = 0; i < 255; ++i) {
        if (profiles[i]) cmsCloseProfile(profiles[i]);
    }
    cmsDeleteContext(context);

    return 0;
}