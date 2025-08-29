// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDictAlloc at cmsnamed.c:1090:21 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsDictAddEntry at cmsnamed.c:1137:19 in lcms2.h
// cmsDictGetEntryList at cmsnamed.c:1189:31 in lcms2.h
// cmsDictNextEntry at cmsnamed.c:1198:31 in lcms2.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(wchar_t)) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsHANDLE hDict = cmsDictAlloc(context);
    if (!hDict) {
        cmsDeleteContext(context);
        return 0;
    }

    wchar_t name[256];
    wchar_t value[256];
    size_t len = Size / (2 * sizeof(wchar_t));
    len = len > 255 ? 255 : len;
    memcpy(name, Data, len * sizeof(wchar_t));
    name[len] = 0;
    memcpy(value, Data + len * sizeof(wchar_t), len * sizeof(wchar_t));
    value[len] = 0;

    cmsDictAddEntry(hDict, name, value, nullptr, nullptr);

    const cmsDICTentry* entry = cmsDictGetEntryList(hDict);
    while (entry) {
        entry = cmsDictNextEntry(entry);
    }

    cmsDictFree(hDict);
    cmsDeleteContext(context);

    return 0;
}