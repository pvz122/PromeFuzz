// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsPluginTHR at cmsplugin.c:546:19 in lcms2.h
// _cmsRealloc at cmserr.c:286:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsCreateMutex at cmserr.c:627:17 in lcms2_plugin.h
// _cmsDestroyMutex at cmserr.c:636:16 in lcms2_plugin.h
// cmsPlugin at cmsplugin.c:541:19 in lcms2.h
// _cmsLockMutex at cmserr.c:646:19 in lcms2_plugin.h
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

extern "C" int LLVMFuzzerTestOneInput_154(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsPluginBase)) {
        return 0;
    }

    cmsContext ContextID = cmsCreateContext(nullptr, nullptr);

    // Fuzz cmsPluginTHR
    cmsPluginBase plugin;
    std::memcpy(&plugin, Data, sizeof(cmsPluginBase));
    cmsPluginTHR(ContextID, &plugin);

    // Fuzz _cmsRealloc
    cmsUInt32Number NewSize = *reinterpret_cast<const cmsUInt32Number*>(Data);
    void* Ptr = _cmsRealloc(ContextID, nullptr, NewSize);
    if (Ptr) {
        _cmsFree(ContextID, Ptr);
    }

    // Fuzz _cmsCreateMutex
    void* mtx = _cmsCreateMutex(ContextID);
    if (mtx) {
        _cmsDestroyMutex(ContextID, mtx);
    }

    // Fuzz cmsPlugin
    cmsPlugin(&plugin);

    // Fuzz _cmsLockMutex
    if (mtx) {
        _cmsLockMutex(ContextID, mtx);
    }

    cmsDeleteContext(ContextID);

    return 0;
}