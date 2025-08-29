// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// _cmsCalloc at cmserr.c:279:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// cmsOpenProfileFromMemTHR at cmsio0.c:1271:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsGetContextUserData at cmsplugin.c:1021:17 in lcms2.h
// cmsIT8LoadFromMem at cmscgats.c:2551:22 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);

    // Fuzz _cmsCalloc
    cmsUInt32Number num = static_cast<cmsUInt32Number>(Data[0]);
    cmsUInt32Number size = static_cast<cmsUInt32Number>(Data[1]);
    void* callocPtr = _cmsCalloc(context, num, size);
    if (callocPtr) _cmsFree(context, callocPtr);

    // Fuzz _cmsMalloc
    if (Size >= 3) {
        cmsUInt32Number mallocSize = static_cast<cmsUInt32Number>(Data[2]);
        void* mallocPtr = _cmsMalloc(context, mallocSize);
        if (mallocPtr) _cmsFree(context, mallocPtr);
    }

    // Fuzz cmsOpenProfileFromMemTHR
    cmsHPROFILE profile = cmsOpenProfileFromMemTHR(context, Data, Size);
    if (profile) cmsCloseProfile(profile);

    // Fuzz cmsGetContextUserData
    void* userData = cmsGetContextUserData(context);

    // Fuzz cmsIT8LoadFromMem
    cmsHANDLE it8Handle = cmsIT8LoadFromMem(context, Data, Size);
    if (it8Handle) cmsIT8Free(it8Handle);

    cmsDeleteContext(context);

    return 0;
}