// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1391:25 in lcms2.h
// cmsCreateMultiprofileTransform at cmsxform.c:1309:25 in lcms2.h
// cmsGetTransformInputFormat at cmsxform.c:1422:27 in lcms2.h
// cmsChangeBuffersFormat at cmsxform.c:1439:19 in lcms2.h
// cmsDoTransform at cmsxform.c:192:16 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_144(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0;

    // Create dummy profiles
    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE proofingProfile = cmsCreate_sRGBProfile();

    // Create a proofing transform
    cmsHTRANSFORM proofingTransform = cmsCreateProofingTransform(
        inputProfile, TYPE_RGB_8, outputProfile, TYPE_RGB_8, proofingProfile, INTENT_PERCEPTUAL, INTENT_PERCEPTUAL, 0);

    // Create a multiprofile transform
    cmsHPROFILE profiles[] = {inputProfile, outputProfile};
    cmsHTRANSFORM multiTransform = cmsCreateMultiprofileTransform(profiles, 2, TYPE_RGB_8, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);

    // Get input format of the proofing transform
    cmsUInt32Number inputFormat = cmsGetTransformInputFormat(proofingTransform);

    // Change buffers format
    cmsChangeBuffersFormat(proofingTransform, TYPE_RGB_8, TYPE_RGB_8);

    // Perform transformation
    uint8_t inputBuffer[3] = {Data[0], Data[1], Data[2]};
    uint8_t outputBuffer[3];
    cmsDoTransform(proofingTransform, inputBuffer, outputBuffer, 1);

    // Cleanup
    cmsDeleteTransform(proofingTransform);
    cmsDeleteTransform(multiTransform);
    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);

    return 0;
}