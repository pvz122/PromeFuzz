// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsMLUalloc at cmsnamed.c:33:19 in lcms2.h
// cmsMLUsetASCII at cmsnamed.c:336:19 in lcms2.h
// cmsMLUsetUTF8 at cmsnamed.c:368:19 in lcms2.h
// cmsMLUtranslationsCodes at cmsnamed.c:696:19 in lcms2.h
// cmsMLUgetTranslation at cmsnamed.c:663:26 in lcms2.h
// cmsMLUsetWide at cmsnamed.c:413:20 in lcms2.h
// cmsMLUfree at cmsnamed.c:476:16 in lcms2.h
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
#include <stdint.h>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    cmsMLU* mlu = cmsMLUalloc(nullptr, 10);
    if (!mlu) return 0;

    char languageCode[3] = {0};
    char countryCode[3] = {0};
    memcpy(languageCode, Data, 3);
    memcpy(countryCode, Data + 3, 3);

    const char* asciiString = reinterpret_cast<const char*>(Data + 6);
    size_t asciiStringLen = Size - 6;

    // Ensure the ASCII string is null-terminated
    char* safeAsciiString = new char[asciiStringLen + 1];
    memcpy(safeAsciiString, asciiString, asciiStringLen);
    safeAsciiString[asciiStringLen] = '\0';

    cmsMLUsetASCII(mlu, languageCode, countryCode, safeAsciiString);
    cmsMLUsetUTF8(mlu, languageCode, countryCode, safeAsciiString);

    char obtainedLanguage[3] = {0};
    char obtainedCountry[3] = {0};
    cmsMLUtranslationsCodes(mlu, 0, obtainedLanguage, obtainedCountry);

    cmsMLUgetTranslation(mlu, languageCode, countryCode, obtainedLanguage, obtainedCountry);

    wchar_t wideString[256] = {0};
    size_t wideStringLen = mbstowcs(wideString, safeAsciiString, asciiStringLen);
    if (wideStringLen != (size_t)-1) {
        cmsMLUsetWide(mlu, languageCode, countryCode, wideString);
    }

    delete[] safeAsciiString;
    cmsMLUfree(mlu);
    return 0;
}