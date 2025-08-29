// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenIOhandlerFromNULL at cmsio0.c:100:26 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsSaveProfileToIOhandler at cmsio0.c:1446:27 in lcms2.h
// cmsSetHeaderRenderingIntent at cmsio0.c:990:16 in lcms2.h
// cmsGetHeaderCreator at cmsio0.c:1020:27 in lcms2.h
// cmsGetPostScriptColorResource at cmsps2.c:1525:27 in lcms2.h
// cmsGetHeaderRenderingIntent at cmsio0.c:984:27 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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
#include <lcms2.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

static cmsUInt32Number dummyRead(cmsIOHANDLER* iohandler, void* Buffer, cmsUInt32Number size, cmsUInt32Number count) {
    return 0;
}

static cmsBool dummySeek(cmsIOHANDLER* iohandler, cmsUInt32Number offset) {
    return true;
}

static cmsBool dummyClose(cmsIOHANDLER* iohandler) {
    return true;
}

static cmsUInt32Number dummyTell(cmsIOHANDLER* iohandler) {
    return 0;
}

static cmsBool dummyWrite(cmsIOHANDLER* iohandler, cmsUInt32Number size, const void* Buffer) {
    return true;
}

static cmsIOHANDLER* createDummyIOHandler(cmsContext context) {
    cmsIOHANDLER* io = cmsOpenIOhandlerFromNULL(context);
    if (!io) return nullptr;

    return io;
}

extern "C" int LLVMFuzzerTestOneInput_128(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    cmsIOHANDLER* io = createDummyIOHandler(context);

    if (!profile || !io) {
        if (profile) cmsCloseProfile(profile);
        if (io) cmsCloseIOhandler(io);
        cmsDeleteContext(context);
        return 0;
    }

    // Fuzz cmsSaveProfileToIOhandler
    cmsSaveProfileToIOhandler(profile, io);

    // Fuzz cmsSetHeaderRenderingIntent
    cmsSetHeaderRenderingIntent(profile, Data[0] % 4);

    // Fuzz cmsGetHeaderCreator
    cmsGetHeaderCreator(profile);

    // Fuzz cmsGetPostScriptColorResource
    cmsGetPostScriptColorResource(context, (cmsPSResourceType)(Data[0] % 2), profile, Data[0] % 4, Data[0], io);

    // Fuzz cmsGetHeaderRenderingIntent
    cmsGetHeaderRenderingIntent(profile);

    cmsCloseProfile(profile);
    cmsCloseIOhandler(io);
    cmsDeleteContext(context);

    return 0;
}