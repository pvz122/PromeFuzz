// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateTransformTHR at cmsxform.c:1331:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateProofingTransformTHR at cmsxform.c:1359:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// _cmsDefaultICCintents at cmscnvrt.c:655:25 in lcms2_plugin.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsGetSupportedIntents at cmscnvrt.c:1192:27 in lcms2.h
// cmsGetSupportedIntents at cmscnvrt.c:1192:27 in lcms2.h
// cmsGetSupportedIntentsTHR at cmscnvrt.c:1157:27 in lcms2.h
// cmsGetSupportedIntentsTHR at cmscnvrt.c:1157:27 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_172(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE proofingProfile = cmsCreate_sRGBProfile();

    cmsUInt32Number inputFormat = TYPE_RGB_8;
    cmsUInt32Number outputFormat = TYPE_RGB_8;
    cmsUInt32Number intent = INTENT_PERCEPTUAL;
    cmsUInt32Number flags = 0;

    // Fuzz cmsCreateTransformTHR
    cmsHTRANSFORM transform = cmsCreateTransformTHR(context, inputProfile, inputFormat, outputProfile, outputFormat, intent, flags);
    if (transform) cmsDeleteTransform(transform);

    // Fuzz cmsCreateProofingTransformTHR
    transform = cmsCreateProofingTransformTHR(context, inputProfile, inputFormat, outputProfile, outputFormat, proofingProfile, intent, intent, flags);
    if (transform) cmsDeleteTransform(transform);

    // Fuzz _cmsDefaultICCintents
    cmsUInt32Number nProfiles = 2;
    cmsUInt32Number intents[] = {INTENT_PERCEPTUAL, INTENT_RELATIVE_COLORIMETRIC};
    cmsHPROFILE profiles[] = {inputProfile, outputProfile};
    cmsBool bpc[] = {FALSE, FALSE};
    cmsFloat64Number adaptationStates[] = {1.0, 1.0};
    cmsPipeline* pipeline = _cmsDefaultICCintents(context, nProfiles, intents, profiles, bpc, adaptationStates, flags);
    if (pipeline) cmsPipelineFree(pipeline);

    // Fuzz cmsGetSupportedIntents
    cmsUInt32Number count = cmsGetSupportedIntents(0, nullptr, nullptr);
    if (count > 0) {
        cmsUInt32Number* codes = (cmsUInt32Number*)malloc(count * sizeof(cmsUInt32Number));
        char** descriptions = (char**)malloc(count * sizeof(char*));
        if (codes && descriptions) {
            cmsGetSupportedIntents(count, codes, descriptions);
        }
        free(codes);
        free(descriptions);
    }

    // Fuzz cmsGetSupportedIntentsTHR
    count = cmsGetSupportedIntentsTHR(context, 0, nullptr, nullptr);
    if (count > 0) {
        cmsUInt32Number* codes = (cmsUInt32Number*)malloc(count * sizeof(cmsUInt32Number));
        char** descriptions = (char**)malloc(count * sizeof(char*));
        if (codes && descriptions) {
            cmsGetSupportedIntentsTHR(context, count, codes, descriptions);
        }
        free(codes);
        free(descriptions);
    }

    cmsCloseProfile(inputProfile);
    cmsCloseProfile(outputProfile);
    cmsCloseProfile(proofingProfile);
    cmsDeleteContext(context);

    return 0;
}