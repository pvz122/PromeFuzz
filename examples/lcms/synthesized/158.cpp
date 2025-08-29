// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// _cmsRealloc at cmserr.c:286:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsCreateMutex at cmserr.c:627:17 in lcms2_plugin.h
// _cmsLockMutex at cmserr.c:646:19 in lcms2_plugin.h
// _cmsDestroyMutex at cmserr.c:636:16 in lcms2_plugin.h
// cmsPluginTHR at cmsplugin.c:546:19 in lcms2.h
// cmsPlugin at cmsplugin.c:541:19 in lcms2.h
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
#include "lcms2.h"
#include "lcms2_plugin.h"

extern "C" int LLVMFuzzerTestOneInput_158(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) {
        return 0;
    }

    cmsUInt32Number newSize = *reinterpret_cast<const cmsUInt32Number*>(Data);
    void* ptr = _cmsRealloc(context, nullptr, newSize);
    if (ptr) {
        _cmsFree(context, ptr);
    }

    void* mutex = _cmsCreateMutex(context);
    if (mutex) {
        _cmsLockMutex(context, mutex);
        _cmsDestroyMutex(context, mutex);
    }

    cmsPluginTHR(context, nullptr);
    cmsPlugin(nullptr);

    cmsDeleteContext(context);
    return 0;
}