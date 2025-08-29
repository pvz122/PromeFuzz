// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsOpenIOhandlerFromNULL at cmsio0.c:100:26 in lcms2.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
// cmsOpenIOhandlerFromStream at cmsio0.c:477:25 in lcms2.h
// cmsOpenProfileFromIOhandlerTHR at cmsio0.c:1158:23 in lcms2.h
// cmsGetProfileIOhandler at cmsio0.c:517:25 in lcms2.h
// cmsOpenProfileFromIOhandler2THR at cmsio0.c:1177:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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
#include "lcms2.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    // Test cmsOpenIOhandlerFromNULL
    cmsIOHANDLER* nullHandler = cmsOpenIOhandlerFromNULL(context);
    if (nullHandler) {
        cmsCloseIOhandler(nullHandler);
    }

    // Test cmsOpenIOhandlerFromStream
    FILE* dummyFile = fopen("./dummy_file", "wb");
    if (dummyFile) {
        fwrite(Data, 1, Size, dummyFile);
        fclose(dummyFile);

        dummyFile = fopen("./dummy_file", "rb");
        if (dummyFile) {
            cmsIOHANDLER* streamHandler = cmsOpenIOhandlerFromStream(context, dummyFile);
            if (streamHandler) {
                // Test cmsOpenProfileFromIOhandlerTHR
                cmsHPROFILE profile = cmsOpenProfileFromIOhandlerTHR(context, streamHandler);
                if (profile) {
                    // Test cmsGetProfileIOhandler
                    cmsIOHANDLER* profileHandler = cmsGetProfileIOhandler(profile);
                    if (profileHandler) {
                        // Test cmsOpenProfileFromIOhandler2THR
                        cmsHPROFILE profile2 = cmsOpenProfileFromIOhandler2THR(context, profileHandler, (Data[0] % 2));
                        if (profile2) {
                            cmsCloseProfile(profile2);
                        }
                    }
                    cmsCloseProfile(profile);
                }
                // Do not close streamHandler here, as it is managed by cmsCloseProfile
            }
            // Do not close dummyFile here, as it is managed by the IOhandler
        }
    }

    cmsDeleteContext(context);
    return 0;
}