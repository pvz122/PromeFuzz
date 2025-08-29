// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenIOhandlerFromNULL at cmsio0.c:100:26 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsSetHeaderRenderingIntent at cmsio0.c:990:16 in lcms2.h
// cmsGetHeaderRenderingIntent at cmsio0.c:984:27 in lcms2.h
// cmsGetHeaderCreator at cmsio0.c:1020:27 in lcms2.h
// cmsSaveProfileToIOhandler at cmsio0.c:1446:27 in lcms2.h
// cmsGetPostScriptColorResource at cmsps2.c:1525:27 in lcms2.h
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

static cmsIOHANDLER* createDummyIOHandler(cmsContext context) {
    cmsIOHANDLER* io = cmsOpenIOhandlerFromNULL(context);
    return io;
}

extern "C" int LLVMFuzzerTestOneInput_149(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    cmsIOHANDLER* io = createDummyIOHandler(context);

    if (!hProfile || !io) {
        if (hProfile) cmsCloseProfile(hProfile);
        if (io) cmsCloseIOhandler(io);
        cmsDeleteContext(context);
        return 0;
    }

    cmsUInt32Number renderingIntent = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsSetHeaderRenderingIntent(hProfile, renderingIntent);
    cmsGetHeaderRenderingIntent(hProfile);
    cmsGetHeaderCreator(hProfile);

    cmsSaveProfileToIOhandler(hProfile, io);

    cmsUInt32Number flags = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsGetPostScriptColorResource(context, cmsPS_RESOURCE_CSA, hProfile, renderingIntent, flags, io);

    cmsCloseProfile(hProfile);
    cmsCloseIOhandler(io);
    cmsDeleteContext(context);

    return 0;
}