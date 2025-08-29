// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateMultiprofileTransformTHR at cmsxform.c:1279:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateExtendedTransform at cmsxform.c:1121:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateProofingTransform at cmsxform.c:1391:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateProofingTransformTHR at cmsxform.c:1359:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// _cmsDefaultICCintents at cmscnvrt.c:655:25 in lcms2_plugin.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext ContextID = cmsCreateContext(nullptr, nullptr);
    if (!ContextID) return 0;

    cmsHPROFILE hProfiles[255];
    cmsUInt32Number nProfiles = Data[0] % 255 + 1;
    cmsUInt32Number InputFormat = TYPE_RGB_8;
    cmsUInt32Number OutputFormat = TYPE_RGB_8;
    cmsUInt32Number Intent = INTENT_PERCEPTUAL;
    cmsUInt32Number dwFlags = 0;

    for (cmsUInt32Number i = 0; i < nProfiles; ++i) {
        hProfiles[i] = cmsCreate_sRGBProfile();
    }

    cmsHTRANSFORM transform1 = cmsCreateMultiprofileTransformTHR(ContextID, hProfiles, nProfiles, InputFormat, OutputFormat, Intent, dwFlags);
    if (transform1) cmsDeleteTransform(transform1);

    cmsBool BPC[255];
    cmsUInt32Number Intents[255];
    cmsFloat64Number AdaptationStates[255];
    for (cmsUInt32Number i = 0; i < nProfiles; ++i) {
        BPC[i] = (Data[i % Size] & 1) ? TRUE : FALSE;
        Intents[i] = Intent;
        AdaptationStates[i] = 1.0;
    }

    cmsHTRANSFORM transform2 = cmsCreateExtendedTransform(ContextID, nProfiles, hProfiles, BPC, Intents, AdaptationStates, nullptr, 0, InputFormat, OutputFormat, dwFlags);
    if (transform2) cmsDeleteTransform(transform2);

    cmsHPROFILE InputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE OutputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE ProofingProfile = cmsCreate_sRGBProfile();

    cmsHTRANSFORM transform3 = cmsCreateProofingTransform(InputProfile, InputFormat, OutputProfile, OutputFormat, ProofingProfile, Intent, Intent, dwFlags);
    if (transform3) cmsDeleteTransform(transform3);

    cmsHTRANSFORM transform4 = cmsCreateProofingTransformTHR(ContextID, InputProfile, InputFormat, OutputProfile, OutputFormat, ProofingProfile, Intent, Intent, dwFlags);
    if (transform4) cmsDeleteTransform(transform4);

    cmsPipeline* pipeline = _cmsDefaultICCintents(ContextID, nProfiles, Intents, hProfiles, BPC, AdaptationStates, dwFlags);
    if (pipeline) cmsPipelineFree(pipeline);

    for (cmsUInt32Number i = 0; i < nProfiles; ++i) {
        cmsCloseProfile(hProfiles[i]);
    }

    cmsCloseProfile(InputProfile);
    cmsCloseProfile(OutputProfile);
    cmsCloseProfile(ProofingProfile);

    cmsDeleteContext(ContextID);

    return 0;
}