// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsReadAlignment at cmsplugin.c:445:19 in lcms2_plugin.h
// _cmsWrite15Fixed16Number at cmsplugin.c:337:20 in lcms2_plugin.h
// _cmsWriteFloat32Number at cmsplugin.c:309:20 in lcms2_plugin.h
// _cmsRead15Fixed16Number at cmsplugin.c:224:20 in lcms2_plugin.h
// _cmsReadFloat32Number at cmsplugin.c:169:20 in lcms2_plugin.h
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

static cmsIOHANDLER* CreateDummyIOHandler(const uint8_t* data, size_t size) {
    cmsIOHANDLER* io = (cmsIOHANDLER*)malloc(sizeof(cmsIOHANDLER));
    if (!io) return nullptr;

    io->stream = fopen("./dummy_file", "wb+");
    if (!io->stream) {
        free(io);
        return nullptr;
    }

    fwrite(data, 1, size, (FILE*)io->stream);
    rewind((FILE*)io->stream);

    io->Read = [](struct _cms_io_handler* iohandler, void* Buffer, cmsUInt32Number size, cmsUInt32Number count) -> cmsUInt32Number {
        return fread(Buffer, size, count, (FILE*)iohandler->stream);
    };

    io->Seek = [](struct _cms_io_handler* iohandler, cmsUInt32Number offset) -> cmsBool {
        return fseek((FILE*)iohandler->stream, offset, SEEK_SET) == 0;
    };

    io->Close = [](struct _cms_io_handler* iohandler) -> cmsBool {
        fclose((FILE*)iohandler->stream);
        free(iohandler);
        return TRUE;
    };

    io->Tell = [](struct _cms_io_handler* iohandler) -> cmsUInt32Number {
        return ftell((FILE*)iohandler->stream);
    };

    io->Write = [](struct _cms_io_handler* iohandler, cmsUInt32Number size, const void* Buffer) -> cmsBool {
        return fwrite(Buffer, size, 1, (FILE*)iohandler->stream) == 1;
    };

    return io;
}

extern "C" int LLVMFuzzerTestOneInput_177(const uint8_t* data, size_t size) {
    if (size < 4) return 0;

    cmsIOHANDLER* io = CreateDummyIOHandler(data, size);
    if (!io) return 0;

    _cmsReadAlignment(io);

    _cmsWrite15Fixed16Number(io, 1.23);
    _cmsWriteFloat32Number(io, 4.56f);

    cmsFloat64Number fixed16Number;
    _cmsRead15Fixed16Number(io, &fixed16Number);

    cmsFloat32Number float32Number;
    _cmsReadFloat32Number(io, &float32Number);

    io->Close(io);

    return 0;
}