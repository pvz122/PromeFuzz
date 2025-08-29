// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateProfilePlaceholder at cmsio0.c:526:23 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsLinkTag at cmsio0.c:2065:19 in lcms2.h
// cmsWriteRawTag at cmsio0.c:2034:19 in lcms2.h
// cmsIsTag at cmsio0.c:708:19 in lcms2.h
// cmsTagLinkedTo at cmsio0.c:2092:28 in lcms2.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsTagSignature) * 2) return 0;

    cmsContext ctx = cmsCreateContext(NULL, NULL);
    cmsHPROFILE hProfile = cmsCreateProfilePlaceholder(ctx);
    if (!hProfile) {
        cmsDeleteContext(ctx);
        return 0;
    }

    cmsTagSignature sig = *reinterpret_cast<const cmsTagSignature*>(Data);
    cmsTagSignature dest = *reinterpret_cast<const cmsTagSignature*>(Data + sizeof(cmsTagSignature));

    cmsLinkTag(hProfile, sig, dest);
    cmsWriteRawTag(hProfile, sig, Data, Size);
    cmsIsTag(hProfile, sig);
    cmsTagLinkedTo(hProfile, sig);

    cmsCloseProfile(hProfile);
    cmsDeleteContext(ctx);
    return 0;
}