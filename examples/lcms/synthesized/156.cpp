// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsPluginTHR at cmsplugin.c:546:19 in lcms2.h
// _cmsRealloc at cmserr.c:286:17 in lcms2_plugin.h
// _cmsCreateMutex at cmserr.c:627:17 in lcms2_plugin.h
// _cmsLockMutex at cmserr.c:646:19 in lcms2_plugin.h
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
#include <lcms2.h>
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_156(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) {
        return 0;
    }

    // Fuzz cmsPluginTHR
    cmsPluginTHR(context, const_cast<void*>(reinterpret_cast<const void*>(Data)));

    // Fuzz _cmsRealloc
    cmsUInt32Number newSize = *reinterpret_cast<const cmsUInt32Number*>(Data);
    void* ptr = malloc(newSize);
    if (ptr) {
        void* newPtr = _cmsRealloc(context, ptr, newSize);
        if (newPtr != ptr) {
            free(newPtr);
        } else {
            free(ptr);
        }
    }

    // Fuzz _cmsCreateMutex
    void* mutex = _cmsCreateMutex(context);
    if (mutex) {
        _cmsLockMutex(context, mutex);
        // Assuming _cmsDestroyMutex is available
        // _cmsDestroyMutex(context, mutex);
    }

    // Fuzz cmsPlugin
    cmsPlugin(const_cast<void*>(reinterpret_cast<const void*>(Data)));

    cmsDeleteContext(context);

    return 0;
}