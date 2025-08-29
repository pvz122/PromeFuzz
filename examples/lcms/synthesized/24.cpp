// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsSetAlarmCodesTHR at cmsxform.c:93:16 in lcms2.h
// cmsSetLogErrorHandler at cmserr.c:503:16 in lcms2.h
// _cmsRealloc at cmserr.c:286:17 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// cmsSetLogErrorHandlerTHR at cmserr.c:489:16 in lcms2.h
// cmsMD5alloc at cmsmd5.c:154:21 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
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

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt16Number) * cmsMAXCHANNELS + sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) {
        return 0;
    }

    cmsUInt16Number alarmCodes[cmsMAXCHANNELS];
    for (int i = 0; i < cmsMAXCHANNELS; ++i) {
        alarmCodes[i] = reinterpret_cast<const cmsUInt16Number*>(Data)[i];
    }
    cmsSetAlarmCodesTHR(context, alarmCodes);

    cmsSetLogErrorHandler(nullptr);

    cmsUInt32Number newSize = reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt16Number) * cmsMAXCHANNELS)[0];
    void* ptr = _cmsRealloc(context, nullptr, newSize);
    if (ptr) {
        _cmsFree(context, ptr);
    }

    cmsSetLogErrorHandlerTHR(context, nullptr);

    cmsHANDLE md5Context = cmsMD5alloc(context);
    if (md5Context) {
        _cmsFree(context, md5Context);
    }

    cmsDeleteContext(context);

    return 0;
}