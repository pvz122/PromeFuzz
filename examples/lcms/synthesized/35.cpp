// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// _cmsReadAlignment at cmsplugin.c:445:19 in lcms2_plugin.h
// _cmsWriteTypeBase at cmsplugin.c:434:20 in lcms2_plugin.h
// cmsGetProfileIOhandler at cmsio0.c:517:25 in lcms2.h
// _cmsReadTypeBase at cmsplugin.c:421:31 in lcms2_plugin.h
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

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy cmsIOHANDLER
    cmsIOHANDLER ioHandler;
    memset(&ioHandler, 0, sizeof(ioHandler));
    ioHandler.ContextID = nullptr;
    ioHandler.UsedSpace = 0;
    ioHandler.PhysicalFile[0] = '\0';
    ioHandler.Read = [](struct _cms_io_handler*, void* Buffer, cmsUInt32Number size, cmsUInt32Number count) -> cmsUInt32Number {
        return size * count;
    };
    ioHandler.Seek = [](struct _cms_io_handler*, cmsUInt32Number offset) -> cmsBool {
        return TRUE;
    };
    ioHandler.Close = [](struct _cms_io_handler*) -> cmsBool {
        return TRUE;
    };
    ioHandler.Tell = [](struct _cms_io_handler*) -> cmsUInt32Number {
        return 0;
    };
    ioHandler.Write = [](struct _cms_io_handler*, cmsUInt32Number size, const void* Buffer) -> cmsBool {
        return TRUE;
    };

    // Fuzz cmsCloseIOhandler
    cmsCloseIOhandler(&ioHandler);

    // Fuzz _cmsReadAlignment
    _cmsReadAlignment(&ioHandler);

    // Fuzz _cmsWriteTypeBase
    _cmsWriteTypeBase(&ioHandler, static_cast<cmsTagTypeSignature>(Data[0]));

    // Fuzz cmsGetProfileIOhandler
    cmsHPROFILE hProfile = nullptr;
    cmsGetProfileIOhandler(hProfile);

    // Fuzz _cmsReadTypeBase
    _cmsReadTypeBase(&ioHandler);

    return 0;
}