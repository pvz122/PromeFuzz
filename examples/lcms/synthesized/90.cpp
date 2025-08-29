// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsOpenIOhandlerFromFile at cmsio0.c:378:25 in lcms2.h
// _cmsReadAlignment at cmsplugin.c:445:19 in lcms2_plugin.h
// _cmsReadXYZNumber at cmsplugin.c:241:20 in lcms2_plugin.h
// _cmsWriteXYZNumber at cmsplugin.c:350:20 in lcms2_plugin.h
// _cmsReadUInt8Number at cmsplugin.c:111:20 in lcms2_plugin.h
// _cmsWriteUInt8Number at cmsplugin.c:258:20 in lcms2_plugin.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy file and write the fuzzing data to it
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Open the dummy file for reading
    file = fopen("./dummy_file", "rb");
    if (!file) return 0;

    // Create a cmsIOHANDLER
    cmsIOHANDLER* io = cmsOpenIOhandlerFromFile(NULL, "./dummy_file", "r");
    if (!io) {
        fclose(file);
        return 0;
    }

    // Fuzz _cmsReadAlignment
    _cmsReadAlignment(io);

    // Fuzz _cmsReadXYZNumber
    cmsCIEXYZ xyz;
    _cmsReadXYZNumber(io, &xyz);

    // Fuzz _cmsWriteXYZNumber
    _cmsWriteXYZNumber(io, &xyz);

    // Fuzz _cmsReadUInt8Number
    cmsUInt8Number n;
    _cmsReadUInt8Number(io, &n);

    // Fuzz _cmsWriteUInt8Number
    _cmsWriteUInt8Number(io, n);

    // Clean up
    cmsCloseIOhandler(io);
    fclose(file);

    return 0;
}