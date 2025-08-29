// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsOpenIOhandlerFromFile at cmsio0.c:378:25 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsCreateDeviceLinkFromCubeFileTHR at cmscgats.c:3206:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsOpenProfileFromFileTHR at cmsio0.c:1203:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsOpenProfileFromFile at cmsio0.c:1231:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsOpenIOhandlerFromFile at cmsio0.c:378:25 in lcms2.h
// cmsOpenProfileFromIOhandlerTHR at cmsio0.c:1158:23 in lcms2.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    const char* filename = "./dummy_file";
    FILE* file = fopen(filename, "wb");
    if (!file) {
        cmsDeleteContext(context);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Fuzz cmsOpenIOhandlerFromFile
    const char* accessMode = (Data[0] & 1) ? "r" : "w";
    cmsIOHANDLER* ioHandler = cmsOpenIOhandlerFromFile(context, filename, accessMode);
    if (ioHandler) {
        cmsCloseIOhandler(ioHandler);
    }

    // Fuzz cmsCreateDeviceLinkFromCubeFileTHR
    cmsHPROFILE deviceLinkProfile = cmsCreateDeviceLinkFromCubeFileTHR(context, filename);
    if (deviceLinkProfile) {
        cmsCloseProfile(deviceLinkProfile);
    }

    // Fuzz cmsOpenProfileFromFileTHR
    cmsHPROFILE profileFromFileTHR = cmsOpenProfileFromFileTHR(context, filename, accessMode);
    if (profileFromFileTHR) {
        cmsCloseProfile(profileFromFileTHR);
    }

    // Fuzz cmsOpenProfileFromFile
    cmsHPROFILE profileFromFile = cmsOpenProfileFromFile(filename, accessMode);
    if (profileFromFile) {
        cmsCloseProfile(profileFromFile);
    }

    // Fuzz cmsOpenProfileFromIOhandlerTHR
    ioHandler = cmsOpenIOhandlerFromFile(context, filename, accessMode);
    if (ioHandler) {
        cmsHPROFILE profileFromIOhandler = cmsOpenProfileFromIOhandlerTHR(context, ioHandler);
        if (profileFromIOhandler) {
            cmsCloseProfile(profileFromIOhandler);
        } else {
            // Do not close ioHandler if cmsOpenProfileFromIOhandlerTHR fails
        }
    }

    cmsDeleteContext(context);
    return 0;
}