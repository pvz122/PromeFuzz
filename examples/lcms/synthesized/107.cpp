// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsOpenProfileFromMem at cmsio0.c:1295:23 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsDetectBlackPoint at cmssamp.c:191:19 in lcms2.h
// cmsDetectDestinationBlackPoint at cmssamp.c:352:19 in lcms2.h
// cmsDetectTAC at cmsgmt.c:462:28 in lcms2.h
// cmsCreateExtendedTransform at cmsxform.c:1121:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsIsIntentSupported at cmsio1.c:864:20 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_107(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 10) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsHPROFILE profile = cmsOpenProfileFromMem(Data, Size);
    if (!profile) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsCIEXYZ blackPoint;
    cmsUInt32Number intent = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number flags = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));

    cmsDetectBlackPoint(&blackPoint, profile, intent, flags);
    cmsDetectDestinationBlackPoint(&blackPoint, profile, intent, flags);

    cmsFloat64Number tac = cmsDetectTAC(profile);

    cmsUInt32Number nProfiles = 1;
    cmsHPROFILE hProfiles[] = {profile};
    cmsBool BPC[] = {FALSE};
    cmsUInt32Number Intents[] = {intent};
    cmsFloat64Number AdaptationStates[] = {1.0};
    cmsHPROFILE hGamutProfile = nullptr;
    cmsUInt32Number nGamutPCSposition = 0;
    cmsUInt32Number InputFormat = 0;
    cmsUInt32Number OutputFormat = 0;

    cmsHTRANSFORM transform = cmsCreateExtendedTransform(context, nProfiles, hProfiles, BPC, Intents, AdaptationStates, hGamutProfile, nGamutPCSposition, InputFormat, OutputFormat, flags);
    if (transform) {
        cmsDeleteTransform(transform);
    }

    cmsIsIntentSupported(profile, intent, 0);

    cmsCloseProfile(profile);
    cmsDeleteContext(context);

    return 0;
}