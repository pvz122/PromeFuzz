// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsAllocProfileSequenceDescription at cmsnamed.c:985:19 in lcms2.h
// cmsDupProfileSequenceDescription at cmsnamed.c:1037:19 in lcms2.h
// cmsFreeProfileSequenceDescription at cmsnamed.c:1017:16 in lcms2.h
// cmsFreeProfileSequenceDescription at cmsnamed.c:1017:16 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCreateTransform at cmsxform.c:1348:32 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCreateTransformTHR at cmsxform.c:1331:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
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
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsUInt32Number n = Data[0] % 256;
    cmsSEQ* seq = cmsAllocProfileSequenceDescription(context, n);
    if (seq) {
        cmsSEQ* dupSeq = cmsDupProfileSequenceDescription(seq);
        if (dupSeq) {
            cmsFreeProfileSequenceDescription(dupSeq);
        }
        cmsFreeProfileSequenceDescription(seq);
    }

    cmsHPROFILE inputProfile = cmsCreate_sRGBProfile();
    cmsHPROFILE outputProfile = cmsCreate_sRGBProfile();
    if (inputProfile && outputProfile) {
        cmsUInt32Number inputFormat = TYPE_RGB_8;
        cmsUInt32Number outputFormat = TYPE_RGB_8;
        cmsUInt32Number intent = INTENT_PERCEPTUAL;
        cmsUInt32Number flags = cmsFLAGS_NOCACHE;

        cmsHTRANSFORM transform = cmsCreateTransform(inputProfile, inputFormat, outputProfile, outputFormat, intent, flags);
        if (transform) {
            cmsDeleteTransform(transform);
        }

        cmsHTRANSFORM transformTHR = cmsCreateTransformTHR(context, inputProfile, inputFormat, outputProfile, outputFormat, intent, flags);
        if (transformTHR) {
            cmsDeleteTransform(transformTHR);
        }
    }

    if (inputProfile) cmsCloseProfile(inputProfile);
    if (outputProfile) cmsCloseProfile(outputProfile);

    cmsDeleteContext(context);

    return 0;
}