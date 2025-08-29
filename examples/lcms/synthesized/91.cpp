// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsSetEncodedICCversion at cmsio0.c:1111:16 in lcms2.h
// cmsGetHeaderCreator at cmsio0.c:1020:27 in lcms2.h
// cmsFormatterForPCSOfProfile at cmspack.c:4044:27 in lcms2.h
// cmsGetHeaderFlags at cmsio0.c:996:27 in lcms2.h
// cmsChannelsOf at cmspcs.c:945:27 in lcms2.h
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
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_91(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) {
        return 0;
    }

    cmsUInt32Number version = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();

    if (hProfile) {
        cmsSetEncodedICCversion(hProfile, version);
        cmsUInt32Number creator = cmsGetHeaderCreator(hProfile);
        cmsUInt32Number formatter = cmsFormatterForPCSOfProfile(hProfile, sizeof(cmsUInt32Number), false);
        cmsUInt32Number flags = cmsGetHeaderFlags(hProfile);
        cmsUInt32Number channels = cmsChannelsOf(cmsSigRgbData);

        cmsCloseProfile(hProfile);
    }

    return 0;
}