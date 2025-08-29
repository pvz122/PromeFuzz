// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenIOhandlerFromNULL at cmsio0.c:100:26 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsSetHeaderRenderingIntent at cmsio0.c:990:16 in lcms2.h
// cmsSaveProfileToIOhandler at cmsio0.c:1446:27 in lcms2.h
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

static cmsIOHANDLER* createDummyIOHandler(cmsContext ctx) {
    cmsIOHANDLER* io = cmsOpenIOhandlerFromNULL(ctx);
    if (!io) return nullptr;

    return io;
}

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsContext ctx = cmsCreateContext(nullptr, nullptr);
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    cmsIOHANDLER* io = createDummyIOHandler(ctx);

    if (!hProfile || !io) {
        if (hProfile) cmsCloseProfile(hProfile);
        if (io) cmsCloseIOhandler(io);
        cmsDeleteContext(ctx);
        return 0;
    }

    cmsUInt32Number renderingIntent = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsSetHeaderRenderingIntent(hProfile, renderingIntent);

    cmsSaveProfileToIOhandler(hProfile, io);

    cmsGetHeaderCreator(hProfile);

    cmsGetPostScriptColorResource(ctx, cmsPS_RESOURCE_CSA, hProfile, renderingIntent, 0, io);

    cmsGetHeaderRenderingIntent(hProfile);

    cmsCloseProfile(hProfile);
    cmsCloseIOhandler(io);
    cmsDeleteContext(ctx);

    return 0;
}