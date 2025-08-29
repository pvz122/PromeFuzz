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
#include <lcms2.h>
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    if (Size < cmsMAXCHANNELS * sizeof(cmsUInt16Number)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) {
        return 0;
    }

    cmsUInt16Number alarmCodes[cmsMAXCHANNELS];
    memcpy(alarmCodes, Data, cmsMAXCHANNELS * sizeof(cmsUInt16Number));

    cmsSetAlarmCodesTHR(context, alarmCodes);

    cmsUInt16Number retrievedAlarmCodes[cmsMAXCHANNELS];
    cmsGetAlarmCodesTHR(context, retrievedAlarmCodes);

    cmsGetAlarmCodes(retrievedAlarmCodes);

    cmsSetAlarmCodes(alarmCodes);

    cmsIOHANDLER ioHandler;
    memset(&ioHandler, 0, sizeof(ioHandler));
    ioHandler.ContextID = context;
    ioHandler.Read = [](struct _cms_io_handler* iohandler, void* Buffer, cmsUInt32Number size, cmsUInt32Number count) -> cmsUInt32Number {
        return count;
    };
    ioHandler.Seek = [](struct _cms_io_handler* iohandler, cmsUInt32Number offset) -> cmsBool {
        return TRUE;
    };
    ioHandler.Close = [](struct _cms_io_handler* iohandler) -> cmsBool {
        return TRUE;
    };
    ioHandler.Tell = [](struct _cms_io_handler* iohandler) -> cmsUInt32Number {
        return 0;
    };

    _cmsReadUInt16Array(&ioHandler, cmsMAXCHANNELS, alarmCodes);

    cmsDeleteContext(context);

    return 0;
}