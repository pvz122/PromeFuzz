// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsMD5computeID at cmsmd5.c:257:19 in lcms2.h
// cmsFormatterForColorspaceOfProfile at cmspack.c:4025:27 in lcms2.h
// cmsSetPCS at cmsio0.c:1075:16 in lcms2.h
// cmsIsCLUT at cmsio1.c:830:20 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsMD5alloc at cmsmd5.c:154:21 in lcms2_plugin.h
// cmsMD5add at cmsmd5.c:172:16 in lcms2_plugin.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_141(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy ICC profile
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return 0;

    // Fuzz cmsMD5computeID
    cmsMD5computeID(hProfile);

    // Fuzz cmsFormatterForColorspaceOfProfile
    cmsUInt32Number nBytes = Data[0] % 2 + 1; // 1 or 2
    cmsBool lIsFloat = Data[0] % 2;
    cmsFormatterForColorspaceOfProfile(hProfile, nBytes, lIsFloat);

    // Fuzz cmsSetPCS
    cmsColorSpaceSignature pcs = static_cast<cmsColorSpaceSignature>(Data[0] % 256);
    cmsSetPCS(hProfile, pcs);

    // Fuzz cmsIsCLUT
    cmsUInt32Number Intent = Data[0] % 4; // 0 to 3
    cmsUInt32Number UsedDirection = Data[0] % 3; // 0 to 2
    cmsIsCLUT(hProfile, Intent, UsedDirection);

    // Create a dummy MD5 context
    cmsContext ContextID = cmsCreateContext(NULL, NULL);
    cmsHANDLE hMD5 = cmsMD5alloc(ContextID);
    if (hMD5) {
        // Fuzz cmsMD5add
        cmsMD5add(hMD5, Data, Size);
        _cmsFree(ContextID, hMD5);
    }
    cmsDeleteContext(ContextID);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}