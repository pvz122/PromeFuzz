// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsWrite15Fixed16Number at cmsplugin.c:337:20 in lcms2_plugin.h
// _cmsDoubleTo8Fixed8 at cmsplugin.c:370:27 in lcms2_plugin.h
// _cms8Fixed8toDouble at cmsplugin.c:365:28 in lcms2_plugin.h
// _cmsDoubleTo15Fixed16 at cmsplugin.c:383:31 in lcms2_plugin.h
// _cms15Fixed16toDouble at cmsplugin.c:377:28 in lcms2_plugin.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "lcms2_plugin.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

static cmsIOHANDLER* CreateDummyIOHandler() {
    cmsIOHANDLER* io = (cmsIOHANDLER*)malloc(sizeof(cmsIOHANDLER));
    if (!io) return nullptr;

    memset(io, 0, sizeof(cmsIOHANDLER));
    io->Write = [](struct _cms_io_handler*, cmsUInt32Number, const void*) { return TRUE; };
    return io;
}

static void FreeDummyIOHandler(cmsIOHANDLER* io) {
    if (io) free(io);
}

extern "C" int LLVMFuzzerTestOneInput_126(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0;

    double value;
    memcpy(&value, Data, sizeof(double));

    cmsIOHANDLER* io = CreateDummyIOHandler();
    if (!io) return 0;

    _cmsWrite15Fixed16Number(io, value);
    _cmsDoubleTo8Fixed8(value);
    _cms8Fixed8toDouble(static_cast<cmsUInt16Number>(value));
    _cmsDoubleTo15Fixed16(value);
    _cms15Fixed16toDouble(static_cast<cmsS15Fixed16Number>(value));

    FreeDummyIOHandler(io);
    return 0;
}