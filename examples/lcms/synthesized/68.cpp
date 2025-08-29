// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDictAlloc at cmsnamed.c:1090:21 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsDictGetEntryList at cmsnamed.c:1189:31 in lcms2.h
// cmsDictNextEntry at cmsnamed.c:1198:31 in lcms2.h
// cmsDictDup at cmsnamed.c:1161:21 in lcms2.h
// cmsDictFree at cmsnamed.c:1101:16 in lcms2.h
// cmsDictFree at cmsnamed.c:1101:16 in lcms2.h
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
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_68(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsHANDLE hDict = cmsDictAlloc(context);
    if (!hDict) {
        cmsDeleteContext(context);
        return 0;
    }

    const cmsDICTentry* entryList = cmsDictGetEntryList(hDict);
    while (entryList) {
        entryList = cmsDictNextEntry(entryList);
    }

    cmsHANDLE hDictDup = cmsDictDup(hDict);
    if (hDictDup) {
        cmsDictFree(hDictDup);
    }

    cmsDictFree(hDict);
    cmsDeleteContext(context);

    return 0;
}