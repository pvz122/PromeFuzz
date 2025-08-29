// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsfilelength at cmserr.c:52:20 in lcms2.h
// cmsOpenIOhandlerFromFile at cmsio0.c:378:25 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsOpenProfileFromStream at cmsio0.c:1264:24 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsOpenProfileFromStreamTHR at cmsio0.c:1237:24 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsOpenIOhandlerFromStream at cmsio0.c:477:25 in lcms2.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE *file = fopen("./dummy_file", "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    file = fopen("./dummy_file", "rb");
    if (!file) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);

    // Fuzz cmsfilelength
    long int file_length = cmsfilelength(file);
    (void)file_length;

    // Fuzz cmsOpenIOhandlerFromFile
    const char *access_mode = (Data[0] % 2) ? "r" : "w";
    cmsIOHANDLER *io_handler_file = cmsOpenIOhandlerFromFile(context, "./dummy_file", access_mode);
    if (io_handler_file) {
        cmsCloseIOhandler(io_handler_file);
    }

    // Fuzz cmsOpenProfileFromStream
    cmsHPROFILE profile_stream = cmsOpenProfileFromStream(file, access_mode);
    if (profile_stream) {
        cmsCloseProfile(profile_stream);
    }

    // Fuzz cmsOpenProfileFromStreamTHR
    cmsHPROFILE profile_stream_thr = cmsOpenProfileFromStreamTHR(context, file, access_mode);
    if (profile_stream_thr) {
        cmsCloseProfile(profile_stream_thr);
    }

    // Fuzz cmsOpenIOhandlerFromStream
    cmsIOHANDLER *io_handler_stream = cmsOpenIOhandlerFromStream(context, file);
    if (io_handler_stream) {
        cmsCloseIOhandler(io_handler_stream);
    }

    cmsDeleteContext(context);

    // Do not close the file here, as it is already closed by the IO handler
    // fclose(file);

    return 0;
}