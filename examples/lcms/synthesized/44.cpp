// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsOpenIOhandlerFromMem at cmsio0.c:238:25 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// _cmsReadUInt64Number at cmsplugin.c:206:21 in lcms2_plugin.h
// _cmsWriteUInt64Number at cmsplugin.c:324:20 in lcms2_plugin.h
// _cmsWriteUInt8Number at cmsplugin.c:258:20 in lcms2_plugin.h
// _cmsWriteAlignment at cmsplugin.c:462:19 in lcms2_plugin.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt64Number)) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    cmsIOHANDLER* io = cmsOpenIOhandlerFromMem(context, const_cast<uint8_t*>(Data), Size, "r");
    if (!io) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsUInt64Number num;
    cmsUInt8Number byte;

    // Test _cmsReadUInt64Number
    _cmsReadUInt64Number(io, &num);

    // Test _cmsWriteUInt64Number
    _cmsWriteUInt64Number(io, &num);

    // Test _cmsWriteUInt8Number
    _cmsWriteUInt8Number(io, byte);

    // Test _cmsWriteAlignment
    _cmsWriteAlignment(io);

    // Test cmsCloseIOhandler
    cmsCloseIOhandler(io);

    cmsDeleteContext(context);
    return 0;
}