// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsIsMatrixShaper at cmsio1.c:806:20 in lcms2.h
// cmsMD5computeID at cmsmd5.c:257:19 in lcms2.h
// cmsWriteRawTag at cmsio0.c:2034:19 in lcms2.h
// cmsSaveProfileToFile at cmsio0.c:1502:20 in lcms2.h
// cmsIsTag at cmsio0.c:708:19 in lcms2.h
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
#include "lcms2.h"
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return 0;

    // Fuzz cmsIsMatrixShaper
    cmsIsMatrixShaper(hProfile);

    // Fuzz cmsMD5computeID
    cmsMD5computeID(hProfile);

    // Fuzz cmsWriteRawTag
    cmsTagSignature sig = static_cast<cmsTagSignature>(Data[0]);
    cmsWriteRawTag(hProfile, sig, Data, Size);

    // Fuzz cmsSaveProfileToFile
    cmsSaveProfileToFile(hProfile, "./dummy_file");

    // Fuzz cmsIsTag
    cmsIsTag(hProfile, sig);

    cmsCloseProfile(hProfile);
    return 0;
}