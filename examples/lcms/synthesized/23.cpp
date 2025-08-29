// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsAllocNamedColorList at cmsnamed.c:749:30 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsAppendNamedColor at cmsnamed.c:815:20 in lcms2.h
// cmsNamedColorIndex at cmsnamed.c:882:26 in lcms2.h
// cmsNamedColorInfo at cmsnamed.c:855:20 in lcms2.h
// cmsDupNamedColorList at cmsnamed.c:787:30 in lcms2.h
// cmsFreeNamedColorList at cmsnamed.c:780:16 in lcms2.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    cmsNAMEDCOLORLIST* namedColorList = cmsAllocNamedColorList(context, 10, 0, "Prefix", "Suffix");
    if (!namedColorList) {
        cmsDeleteContext(context);
        return 0;
    }

    char colorName[256];
    cmsUInt16Number PCS[3] = {0};
    cmsUInt16Number Colorant[cmsMAXCHANNELS] = {0};

    size_t nameLength = Size > 255 ? 255 : Size;
    memcpy(colorName, Data, nameLength);
    colorName[nameLength] = '\0';

    cmsAppendNamedColor(namedColorList, colorName, PCS, Colorant);

    cmsInt32Number index = cmsNamedColorIndex(namedColorList, colorName);

    if (index != -1) {
        char retrievedName[256];
        char retrievedPrefix[33];
        char retrievedSuffix[33];
        cmsNamedColorInfo(namedColorList, index, retrievedName, retrievedPrefix, retrievedSuffix, PCS, Colorant);
    }

    cmsNAMEDCOLORLIST* dupList = cmsDupNamedColorList(namedColorList);
    if (dupList) {
        cmsFreeNamedColorList(dupList);
    }

    cmsFreeNamedColorList(namedColorList);
    cmsDeleteContext(context);

    return 0;
}