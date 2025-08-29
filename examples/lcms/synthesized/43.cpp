// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsSetHeaderManufacturer at cmsio0.c:1014:16 in lcms2.h
// cmsGetEncodedICCversion at cmsio0.c:1105:27 in lcms2.h
// cmsGetHeaderModel at cmsio0.c:1026:27 in lcms2.h
// cmsGetHeaderFlags at cmsio0.c:996:27 in lcms2.h
// cmsCreateMultiprofileTransform at cmsxform.c:1309:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsUInt32Number manufacturer = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return 0;

    cmsSetHeaderManufacturer(hProfile, manufacturer);

    cmsUInt32Number version = cmsGetEncodedICCversion(hProfile);
    cmsUInt32Number model = cmsGetHeaderModel(hProfile);
    cmsUInt32Number flags = cmsGetHeaderFlags(hProfile);

    cmsHPROFILE hProfiles[] = {hProfile};
    cmsHTRANSFORM hTransform = cmsCreateMultiprofileTransform(hProfiles, 1, TYPE_RGB_8, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);

    if (hTransform) cmsDeleteTransform(hTransform);
    cmsCloseProfile(hProfile);

    return 0;
}