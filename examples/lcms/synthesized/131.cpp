// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateTransform at cmsxform.c:1348:32 in lcms2.h
// cmsDoTransform at cmsxform.c:192:16 in lcms2.h
// cmsDoTransformStride at cmsxform.c:211:16 in lcms2.h
// cmsDoTransformLineStride at cmsxform.c:229:16 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1391:25 in lcms2.h
// cmsDoTransform at cmsxform.c:192:16 in lcms2.h
// cmsDoTransformStride at cmsxform.c:211:16 in lcms2.h
// cmsDoTransformLineStride at cmsxform.c:229:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE proofingProfile = cmsCreate_sRGBProfile();

    cmsUInt32Number inputFormat = TYPE_RGB_8;
    cmsUInt32Number outputFormat = TYPE_RGB_8;
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = cmsFLAGS_NOCACHE;

    cmsHTRANSFORM transform = cmsCreateTransform(inputProfile, inputFormat, outputProfile, outputFormat, intent, flags);
    if (transform) {
        uint8_t* inputBuffer = new uint8_t[Size];
        uint8_t* outputBuffer = new uint8_t[Size];
        memcpy(inputBuffer, Data, Size);

        cmsDoTransform(transform, inputBuffer, outputBuffer, Size / 3);
        cmsDoTransformStride(transform, inputBuffer, outputBuffer, Size / 3, Size / 3);
        cmsDoTransformLineStride(transform, inputBuffer, outputBuffer, Size / 3, 1, Size, Size, Size, Size);

        delete[] inputBuffer;
        delete[] outputBuffer;
        cmsDeleteTransform(transform);
    }

    cmsHTRANSFORM proofingTransform = cmsCreateProofingTransform(inputProfile, inputFormat, outputProfile, outputFormat, proofingProfile, intent, intent, flags);
    if (proofingTransform) {
        uint8_t* inputBuffer = new uint8_t[Size];
        uint8_t* outputBuffer = new uint8_t[Size];
        memcpy(inputBuffer, Data, Size);

        cmsDoTransform(proofingTransform, inputBuffer, outputBuffer, Size / 3);
        cmsDoTransformStride(proofingTransform, inputBuffer, outputBuffer, Size / 3, Size / 3);
        cmsDoTransformLineStride(proofingTransform, inputBuffer, outputBuffer, Size / 3, 1, Size, Size, Size, Size);

        delete[] inputBuffer;
        delete[] outputBuffer;
        cmsDeleteTransform(proofingTransform);
    }

    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);

    return 0;
}