// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateDeviceLinkFromCubeFile at cmscgats.c:3280:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsIT8LoadFromFile at cmscgats.c:2598:22 in lcms2.h
// cmsIT8GetProperty at cmscgats.c:1573:23 in lcms2.h
// cmsIT8GetPropertyMulti at cmscgats.c:1595:23 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
// cmsIT8LoadFromMem at cmscgats.c:2551:22 in lcms2.h
// cmsIT8GetProperty at cmscgats.c:1573:23 in lcms2.h
// cmsIT8GetPropertyMulti at cmscgats.c:1595:23 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_74(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    // Create a dummy file for cmsCreateDeviceLinkFromCubeFile
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        cmsDeleteContext(context);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Test cmsCreateDeviceLinkFromCubeFile
    cmsHPROFILE profile = cmsCreateDeviceLinkFromCubeFile("./dummy_file");
    if (profile) {
        cmsCloseProfile(profile);
    }

    // Test cmsIT8LoadFromFile
    cmsHANDLE it8File = cmsIT8LoadFromFile(context, "./dummy_file");
    if (it8File) {
        const char* prop = cmsIT8GetProperty(it8File, "KEY");
        if (prop) {
            // Do nothing
        }
        const char* propMulti = cmsIT8GetPropertyMulti(it8File, "KEY", "SUBKEY");
        if (propMulti) {
            // Do nothing
        }
        cmsIT8Free(it8File);
    }

    // Test cmsIT8LoadFromMem
    cmsHANDLE it8Mem = cmsIT8LoadFromMem(context, Data, Size);
    if (it8Mem) {
        const char* prop = cmsIT8GetProperty(it8Mem, "KEY");
        if (prop) {
            // Do nothing
        }
        const char* propMulti = cmsIT8GetPropertyMulti(it8Mem, "KEY", "SUBKEY");
        if (propMulti) {
            // Do nothing
        }
        cmsIT8Free(it8Mem);
    }

    cmsDeleteContext(context);
    return 0;
}