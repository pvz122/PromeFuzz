// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsWriteUInt64Number at cmsplugin.c:324:20 in lcms2_plugin.h
// _cmsWrite15Fixed16Number at cmsplugin.c:337:20 in lcms2_plugin.h
// _cmsReadUInt64Number at cmsplugin.c:206:21 in lcms2_plugin.h
// _cmsRead15Fixed16Number at cmsplugin.c:224:20 in lcms2_plugin.h
// _cmsAdjustEndianess64 at cmsplugin.c:79:17 in lcms2_plugin.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <lcms2_plugin.h>
#include <stdint.h>
#include <cstdio>
#include <cstdlib>

static cmsIOHANDLER* create_dummy_io_handler() {
    cmsIOHANDLER* io = (cmsIOHANDLER*)malloc(sizeof(cmsIOHANDLER));
    if (!io) return nullptr;

    io->stream = fopen("./dummy_file", "wb+");
    if (!io->stream) {
        free(io);
        return nullptr;
    }

    io->Write = [](struct _cms_io_handler* iohandler, cmsUInt32Number size, const void* Buffer) -> cmsBool {
        return fwrite(Buffer, size, 1, (FILE*)iohandler->stream) == 1;
    };

    io->Read = [](struct _cms_io_handler* iohandler, void* Buffer, cmsUInt32Number size, cmsUInt32Number count) -> cmsUInt32Number {
        return fread(Buffer, size, count, (FILE*)iohandler->stream);
    };

    io->Seek = [](struct _cms_io_handler* iohandler, cmsUInt32Number offset) -> cmsBool {
        return fseek((FILE*)iohandler->stream, offset, SEEK_SET) == 0;
    };

    io->Tell = [](struct _cms_io_handler* iohandler) -> cmsUInt32Number {
        return ftell((FILE*)iohandler->stream);
    };

    io->Close = [](struct _cms_io_handler* iohandler) -> cmsBool {
        fclose((FILE*)iohandler->stream);
        free(iohandler);
        return TRUE;
    };

    return io;
}

extern "C" int LLVMFuzzerTestOneInput_89(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt64Number) + sizeof(cmsFloat64Number)) return 0;

    cmsIOHANDLER* io = create_dummy_io_handler();
    if (!io) return 0;

    cmsUInt64Number num64 = *(cmsUInt64Number*)Data;
    cmsFloat64Number numFloat = *(cmsFloat64Number*)(Data + sizeof(cmsUInt64Number));

    _cmsWriteUInt64Number(io, &num64);
    _cmsWrite15Fixed16Number(io, numFloat);

    cmsUInt64Number readNum64;
    cmsFloat64Number readNumFloat;

    fseek((FILE*)io->stream, 0, SEEK_SET);
    _cmsReadUInt64Number(io, &readNum64);
    _cmsRead15Fixed16Number(io, &readNumFloat);

    cmsUInt64Number adjustedNum64;
    _cmsAdjustEndianess64(&adjustedNum64, &num64);

    io->Close(io);

    return 0;
}