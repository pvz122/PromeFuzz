// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsOpenIOhandlerFromNULL at cmsio0.c:100:26 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// _cmsWriteAlignment at cmsplugin.c:462:19 in lcms2_plugin.h
// _cmsIOPrintf at cmsplugin.c:482:19 in lcms2_plugin.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8SaveToFile at cmscgats.c:2002:19 in lcms2.h
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
#include "lcms2.h"
#include "lcms2_plugin.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_145(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    // Test cmsOpenIOhandlerFromNULL
    cmsIOHANDLER* ioHandler = cmsOpenIOhandlerFromNULL(context);
    if (!ioHandler) {
        cmsDeleteContext(context);
        return 0;
    }

    // Test _cmsWriteAlignment
    _cmsWriteAlignment(ioHandler);

    // Test _cmsIOPrintf
    _cmsIOPrintf(ioHandler, "Test format: %d", 123);

    // Test cmsCloseIOhandler
    cmsCloseIOhandler(ioHandler);

    // Test cmsIT8SaveToFile
    cmsHANDLE it8Handle = cmsIT8Alloc(context);
    if (it8Handle) {
        cmsIT8SaveToFile(it8Handle, "./dummy_file");
        cmsIT8Free(it8Handle);
    }

    cmsDeleteContext(context);
    return 0;
}