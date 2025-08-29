// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsMLUalloc at cmsnamed.c:33:19 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsMLUdup at cmsnamed.c:430:19 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsMLUgetASCII at cmsnamed.c:542:27 in lcms2.h
// cmsMLUtranslationsCount at cmsnamed.c:689:27 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsMLU* mlu = cmsMLUalloc(context, 2);
    if (!mlu) {
        cmsDeleteContext(context);
        return 0;
    }

    // Fuzz cmsMLUdup
    cmsMLU* mlu_dup = cmsMLUdup(mlu);
    if (mlu_dup) {
        cmsMLUfree(mlu_dup);
    }

    // Fuzz cmsMLUgetASCII
    char languageCode[3] = {static_cast<char>(Data[0]), static_cast<char>(Data[1]), '\0'};
    char countryCode[3] = {static_cast<char>(Data[2]), static_cast<char>(Data[3]), '\0'};
    char buffer[256];
    cmsMLUgetASCII(mlu, languageCode, countryCode, buffer, sizeof(buffer));

    // Fuzz cmsMLUtranslationsCount
    cmsMLUtranslationsCount(mlu);

    // Cleanup
    cmsMLUfree(mlu);
    cmsDeleteContext(context);

    return 0;
}