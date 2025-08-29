// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1391:25 in lcms2.h
// cmsGetTransformInputFormat at cmsxform.c:1422:27 in lcms2.h
// cmsChangeBuffersFormat at cmsxform.c:1439:19 in lcms2.h
// cmsDoTransform at cmsxform.c:192:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 10) return 0;

    cmsUInt32Number inputFormat = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number outputFormat = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number intent = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 2);
    cmsUInt32Number proofingIntent = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 3);
    cmsUInt32Number flags = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 4);

    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE proofingProfile = cmsCreate_sRGBProfile();

    cmsHTRANSFORM transform = cmsCreateProofingTransform(inputProfile, inputFormat, outputProfile, outputFormat, proofingProfile, intent, proofingIntent, flags);
    if (transform) {
        cmsUInt32Number retrievedInputFormat = cmsGetTransformInputFormat(transform);
        cmsChangeBuffersFormat(transform, inputFormat, outputFormat);

        uint8_t inputBuffer[1024];
        uint8_t outputBuffer[1024];
        memset(inputBuffer, 0, sizeof(inputBuffer));
        memcpy(inputBuffer, Data, Size < sizeof(inputBuffer) ? Size : sizeof(inputBuffer));
        cmsDoTransform(transform, inputBuffer, outputBuffer, sizeof(inputBuffer));

        cmsDeleteTransform(transform);
    }

    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);

    return 0;
}