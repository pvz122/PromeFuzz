// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsSetAlarmCodesTHR at cmsxform.c:93:16 in lcms2.h
// cmsGetAlarmCodesTHR at cmsxform.c:104:16 in lcms2.h
// cmsGetAlarmCodes at cmsxform.c:120:16 in lcms2.h
// cmsSetAlarmCodes at cmsxform.c:113:16 in lcms2.h
// _cmsReadUInt16Array at cmsplugin.c:137:20 in lcms2_plugin.h
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
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_122(const uint8_t *Data, size_t Size) {
    if (Size < cmsMAXCHANNELS * sizeof(cmsUInt16Number)) {
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

    cmsUInt16Number retrievedAlarmCodes[cmsMAXCHANNELS];
    cmsGetAlarmCodesTHR(context, retrievedAlarmCodes);

    cmsGetAlarmCodes(retrievedAlarmCodes);

    cmsSetAlarmCodes(alarmCodes);

    cmsIOHANDLER ioHandler = {0};
    ioHandler.Read = [](cmsIOHANDLER* iohandler, void* Buffer, cmsUInt32Number size, cmsUInt32Number count) -> cmsUInt32Number {
        return count; // Mock read function to avoid SEGV
    };
    cmsUInt16Number array[cmsMAXCHANNELS];
    _cmsReadUInt16Array(&ioHandler, cmsMAXCHANNELS, array);

    cmsDeleteContext(context);

    return 0;
}