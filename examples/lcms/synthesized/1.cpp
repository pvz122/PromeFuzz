// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// cmsGetPostScriptCSA at cmsps2.c:1579:27 in lcms2.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// cmsGetPostScriptCSA at cmsps2.c:1579:27 in lcms2.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
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

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    if (!profile) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsUInt32Number intent = Data[0] % 4;
    cmsUInt32Number flags = 0;
    cmsUInt32Number bufferLen = 1024;
    void* buffer = _cmsMalloc(context, bufferLen);

    cmsGetPostScriptCSA(context, profile, intent, flags, buffer, bufferLen);
    void* allocatedMemory = _cmsMalloc(context, 256);
    cmsGetPostScriptCSA(context, profile, intent, flags, nullptr, 0);
    _cmsFree(context, buffer);
    _cmsFree(context, allocatedMemory);

    cmsCloseProfile(profile);
    cmsDeleteContext(context);

    return 0;
}