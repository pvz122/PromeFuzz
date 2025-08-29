// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsSetAdaptationState at cmsxform.c:77:28 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsSetAdaptationStateTHR at cmsxform.c:57:28 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateMultiprofileTransformTHR at cmsxform.c:1279:25 in lcms2.h
// cmsCreateExtendedTransform at cmsxform.c:1121:25 in lcms2.h
// _cmsDefaultICCintents at cmscnvrt.c:655:25 in lcms2_plugin.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_123(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number)) {
        return 0;
    }

    cmsFloat64Number adaptationState = *reinterpret_cast<const cmsFloat64Number*>(Data);
    cmsSetAdaptationState(adaptationState);

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    cmsSetAdaptationStateTHR(context, adaptationState);

    cmsHPROFILE profiles[1];
    profiles[0] = cmsCreate_sRGBProfile();
    cmsCreateMultiprofileTransformTHR(context, profiles, 1, TYPE_RGB_8, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);

    cmsBool bpc[1] = { TRUE };
    cmsUInt32Number intents[1] = { INTENT_PERCEPTUAL };
    cmsFloat64Number adaptationStates[1] = { adaptationState };
    cmsCreateExtendedTransform(context, 1, profiles, bpc, intents, adaptationStates, nullptr, 0, TYPE_RGB_8, TYPE_RGB_8, 0);

    cmsPipeline* pipeline = _cmsDefaultICCintents(context, 1, intents, profiles, bpc, adaptationStates, 0);
    if (pipeline) {
        cmsPipelineFree(pipeline);
    }

    cmsCloseProfile(profiles[0]);
    cmsDeleteContext(context);

    return 0;
}