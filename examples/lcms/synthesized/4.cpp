// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsGetPostScriptCRD at cmsps2.c:1552:27 in lcms2.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// cmsGetPostScriptCRD at cmsps2.c:1552:27 in lcms2.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(cmsUInt32Number)) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsUInt32Number intent = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number flags = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number bufferLen = *reinterpret_cast<const cmsUInt32Number*>(Data + 2 * sizeof(cmsUInt32Number));

    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    if (!profile) {
        cmsDeleteContext(context);
        return 0;
    }

    void* buffer = nullptr;
    cmsUInt32Number result = cmsGetPostScriptCRD(context, profile, intent, flags, buffer, bufferLen);

    void* allocatedMemory = _cmsMalloc(context, bufferLen);
    if (allocatedMemory) {
        result = cmsGetPostScriptCRD(context, profile, intent, flags, allocatedMemory, bufferLen);
        _cmsFree(context, allocatedMemory);
    }

    cmsCloseProfile(profile);
    cmsDeleteContext(context);

    return 0;
}