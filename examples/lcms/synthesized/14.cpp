// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsPluginTHR at cmsplugin.c:546:19 in lcms2.h
// _cmsCreateMutex at cmserr.c:627:17 in lcms2_plugin.h
// _cmsLockMutex at cmserr.c:646:19 in lcms2_plugin.h
// _cmsDestroyMutex at cmserr.c:636:16 in lcms2_plugin.h
// cmsGetContextUserData at cmsplugin.c:1021:17 in lcms2.h
// cmsCreate_sRGBProfileTHR at cmsvirt.c:642:23 in lcms2.h
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
#include <lcms2_plugin.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void*)) return 0;

    cmsContext context = cmsCreateContext(NULL, NULL);
    if (!context) return 0;

    // Fuzz cmsPluginTHR
    void* plugin = reinterpret_cast<void*>(const_cast<uint8_t*>(Data));
    cmsPluginTHR(context, plugin);

    // Fuzz _cmsCreateMutex
    void* mutex = _cmsCreateMutex(context);
    if (mutex) {
        // Fuzz _cmsLockMutex
        _cmsLockMutex(context, mutex);
        _cmsDestroyMutex(context, mutex); // Free the mutex
    }

    // Fuzz cmsGetContextUserData
    cmsGetContextUserData(context);

    // Fuzz cmsCreate_sRGBProfileTHR
    cmsHPROFILE profile = cmsCreate_sRGBProfileTHR(context);
    if (profile) {
        cmsCloseProfile(profile);
    }

    cmsDeleteContext(context);

    return 0;
}