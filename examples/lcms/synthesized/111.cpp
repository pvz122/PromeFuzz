// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsAllocNamedColorList at cmsnamed.c:749:30 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsDupNamedColorList at cmsnamed.c:787:30 in lcms2.h
// cmsFreeNamedColorList at cmsnamed.c:780:16 in lcms2.h
// cmsNamedColorCount at cmsnamed.c:848:27 in lcms2.h
// cmsCreateTransform at cmsxform.c:1348:32 in lcms2.h
// cmsGetNamedColorList at cmsnamed.c:967:30 in lcms2.h
// cmsFreeNamedColorList at cmsnamed.c:780:16 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsFreeNamedColorList at cmsnamed.c:780:16 in lcms2.h
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
#include <stdint.h>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_111(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsUInt32Number nColors = Data[0] % 256;
    cmsUInt32Number colorantCount = Data[0] % 256;
    const char* prefix = "Prefix";
    const char* suffix = "Suffix";

    cmsNAMEDCOLORLIST* namedColorList = cmsAllocNamedColorList(context, nColors, colorantCount, prefix, suffix);
    if (!namedColorList) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsNAMEDCOLORLIST* dupNamedColorList = cmsDupNamedColorList(namedColorList);
    if (dupNamedColorList) {
        cmsFreeNamedColorList(dupNamedColorList);
    }

    cmsUInt32Number colorCount = cmsNamedColorCount(namedColorList);

    cmsHTRANSFORM transform = cmsCreateTransform(nullptr, 0, nullptr, 0, 0, 0);
    if (transform) {
        cmsNAMEDCOLORLIST* namedColorListFromTransform = cmsGetNamedColorList(transform);
        if (namedColorListFromTransform) {
            cmsFreeNamedColorList(namedColorListFromTransform);
        }
        cmsDeleteTransform(transform);
    }

    cmsFreeNamedColorList(namedColorList);
    cmsDeleteContext(context);

    return 0;
}