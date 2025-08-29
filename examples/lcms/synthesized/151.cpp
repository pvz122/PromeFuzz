// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsOpenIOhandlerFromFile at cmsio0.c:378:25 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsOpenProfileFromStream at cmsio0.c:1264:24 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsOpenProfileFromStreamTHR at cmsio0.c:1237:24 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsOpenProfileFromFileTHR at cmsio0.c:1203:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsOpenProfileFromFile at cmsio0.c:1231:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_151(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    const char* fileName = "./dummy_file";
    FILE* file = fopen(fileName, "wb");
    if (!file) {
        cmsDeleteContext(context);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    const char* accessMode = (Data[0] & 1) ? "r" : "w";

    cmsIOHANDLER* handler = cmsOpenIOhandlerFromFile(context, fileName, accessMode);
    if (handler) {
        cmsCloseIOhandler(handler);
    }

    file = fopen(fileName, "rb");
    if (file) {
        cmsHPROFILE profile = cmsOpenProfileFromStream(file, accessMode);
        if (profile) {
            cmsCloseProfile(profile);
        }
        // Do not close the file here, as cmsOpenProfileFromStream may have taken ownership
    }

    file = fopen(fileName, "rb");
    if (file) {
        cmsHPROFILE profile = cmsOpenProfileFromStreamTHR(context, file, accessMode);
        if (profile) {
            cmsCloseProfile(profile);
        }
        // Do not close the file here, as cmsOpenProfileFromStreamTHR may have taken ownership
    }

    cmsHPROFILE profile = cmsOpenProfileFromFileTHR(context, fileName, accessMode);
    if (profile) {
        cmsCloseProfile(profile);
    }

    profile = cmsOpenProfileFromFile(fileName, accessMode);
    if (profile) {
        cmsCloseProfile(profile);
    }

    cmsDeleteContext(context);
    return 0;
}