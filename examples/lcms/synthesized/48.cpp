// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsMLUalloc at cmsnamed.c:33:19 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsMLUgetASCII at cmsnamed.c:542:27 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsMLUgetWide at cmsnamed.c:629:27 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsMLUgetUTF8 at cmsnamed.c:590:27 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsGetProfileInfoASCII at cmsio1.c:1021:28 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsGetProfileInfoUTF8 at cmsio1.c:1031:28 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    char LanguageCode[3] = {0};
    char CountryCode[3] = {0};
    memcpy(LanguageCode, Data, 3);
    memcpy(CountryCode, Data + 3, 3);

    cmsMLU* mlu = cmsMLUalloc(nullptr, 1);
    if (!mlu) return 0;

    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) {
        cmsMLUfree(mlu);
        return 0;
    }

    char buffer[256] = {0};
    cmsUInt32Number bufferSize = sizeof(buffer);

    if (cmsMLUgetASCII(mlu, LanguageCode, CountryCode, buffer, bufferSize) == 0) {
        cmsMLUfree(mlu);
        cmsCloseProfile(hProfile);
        return 0;
    }

    if (cmsMLUgetWide(mlu, LanguageCode, CountryCode, reinterpret_cast<wchar_t*>(buffer), bufferSize / sizeof(wchar_t)) == 0) {
        cmsMLUfree(mlu);
        cmsCloseProfile(hProfile);
        return 0;
    }

    if (cmsMLUgetUTF8(mlu, LanguageCode, CountryCode, buffer, bufferSize) == 0) {
        cmsMLUfree(mlu);
        cmsCloseProfile(hProfile);
        return 0;
    }

    if (cmsGetProfileInfoASCII(hProfile, cmsInfoDescription, LanguageCode, CountryCode, buffer, bufferSize) == 0) {
        cmsMLUfree(mlu);
        cmsCloseProfile(hProfile);
        return 0;
    }

    if (cmsGetProfileInfoUTF8(hProfile, cmsInfoDescription, LanguageCode, CountryCode, buffer, bufferSize) == 0) {
        cmsMLUfree(mlu);
        cmsCloseProfile(hProfile);
        return 0;
    }

    cmsMLUfree(mlu);
    cmsCloseProfile(hProfile);

    return 0;
}