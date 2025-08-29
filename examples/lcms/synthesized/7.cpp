// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// cmsGetProfileInfo at cmsio1.c:1010:27 in lcms2.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
// _cmsMalloc at cmserr.c:265:17 in lcms2_plugin.h
// cmsGetProfileInfo at cmsio1.c:1010:27 in lcms2.h
// _cmsFree at cmserr.c:293:16 in lcms2_plugin.h
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
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsHPROFILE profile = cmsCreate_sRGBProfile();
    if (!profile) {
        cmsDeleteContext(context);
        return 0;
    }

    char languageCode[3] = {static_cast<char>(Data[0]), static_cast<char>(Data[1]), '\0'};
    char countryCode[3] = {static_cast<char>(Data[2]), static_cast<char>(Data[3]), '\0'};
    cmsUInt32Number bufferSize = static_cast<cmsUInt32Number>(Data[4]) << 8 | Data[5];
    wchar_t* buffer = static_cast<wchar_t*>(_cmsMalloc(context, bufferSize * sizeof(wchar_t)));

    cmsGetProfileInfo(profile, cmsInfoDescription, languageCode, countryCode, buffer, bufferSize);
    _cmsFree(context, buffer);

    buffer = static_cast<wchar_t*>(_cmsMalloc(context, bufferSize * sizeof(wchar_t)));
    cmsGetProfileInfo(profile, cmsInfoManufacturer, languageCode, countryCode, buffer, bufferSize);
    _cmsFree(context, buffer);

    cmsCloseProfile(profile);
    cmsDeleteContext(context);

    return 0;
}