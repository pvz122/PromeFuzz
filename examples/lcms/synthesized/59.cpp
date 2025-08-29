// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenIOhandlerFromFile at cmsio0.c:378:25 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// _cmsReadUInt16Number at cmsplugin.c:124:20 in lcms2_plugin.h
// _cmsReadUInt16Array at cmsplugin.c:137:20 in lcms2_plugin.h
// _cmsWriteUInt16Number at cmsplugin.c:268:20 in lcms2_plugin.h
// _cmsReadUInt32Number at cmsplugin.c:156:20 in lcms2_plugin.h
// _cmsWriteUInt16Array at cmsplugin.c:281:20 in lcms2_plugin.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>

static cmsIOHANDLER* createDummyIOHandler(const uint8_t* data, size_t size) {
    FILE* file = fopen("./dummy_file", "wb");
    if (!file) return nullptr;
    fwrite(data, 1, size, file);
    fclose(file);

    file = fopen("./dummy_file", "rb");
    if (!file) return nullptr;

    cmsIOHANDLER* io = cmsOpenIOhandlerFromFile(nullptr, "./dummy_file", "r");
    if (!io) {
        fclose(file);
        return nullptr;
    }

    return io;
}

static void cleanupDummyIOHandler(cmsIOHANDLER* io) {
    if (io) {
        cmsCloseIOhandler(io);
    }
    remove("./dummy_file");
}

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t* data, size_t size) {
    if (size < 2) return 0;

    cmsIOHANDLER* io = createDummyIOHandler(data, size);
    if (!io) return 0;

    cmsUInt16Number u16;
    cmsUInt32Number u32;
    cmsUInt16Number array[16];
    cmsUInt32Number arraySize = size / 2 > 16 ? 16 : size / 2;

    _cmsReadUInt16Number(io, &u16);
    _cmsReadUInt16Array(io, arraySize, array);
    _cmsWriteUInt16Number(io, u16);
    _cmsReadUInt32Number(io, &u32);
    _cmsWriteUInt16Array(io, arraySize, array);

    cleanupDummyIOHandler(io);
    return 0;
}