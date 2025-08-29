// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
// cmsIT8GetProperty at cmscgats.c:1573:23 in lcms2.h
// cmsIT8DefineDblFormat at cmscgats.c:3036:16 in lcms2.h
// cmsIT8GetData at cmscgats.c:2857:23 in lcms2.h
// cmsIT8GetSheetType at cmscgats.c:1503:23 in lcms2.h
// cmsIT8GetPropertyMulti at cmscgats.c:1595:23 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy IT8 handle
    cmsHANDLE hIT8 = cmsIT8Alloc(nullptr);
    if (!hIT8) return 0;

    // Generate random strings from the input data
    const char* str1 = reinterpret_cast<const char*>(Data);
    size_t str1_len = strnlen(str1, Size);
    const char* str2 = reinterpret_cast<const char*>(Data + str1_len);
    size_t str2_len = strnlen(str2, Size - str1_len);

    // Ensure str1 is null-terminated
    char* safe_str1 = (char*)malloc(str1_len + 1);
    if (safe_str1) {
        memcpy(safe_str1, str1, str1_len);
        safe_str1[str1_len] = '\0';
    } else {
        cmsIT8Free(hIT8);
        return 0;
    }

    // Ensure str2 is null-terminated
    char* safe_str2 = (char*)malloc(str2_len + 1);
    if (safe_str2) {
        memcpy(safe_str2, str2, str2_len);
        safe_str2[str2_len] = '\0';
    } else {
        free(safe_str1);
        cmsIT8Free(hIT8);
        return 0;
    }

    // Fuzz cmsIT8GetProperty
    cmsIT8GetProperty(hIT8, safe_str1);

    // Fuzz cmsIT8DefineDblFormat
    cmsIT8DefineDblFormat(hIT8, safe_str1);

    // Fuzz cmsIT8GetData
    cmsIT8GetData(hIT8, safe_str1, safe_str2);

    // Fuzz cmsIT8GetSheetType
    cmsIT8GetSheetType(hIT8);

    // Fuzz cmsIT8GetPropertyMulti
    cmsIT8GetPropertyMulti(hIT8, safe_str1, safe_str2);

    // Clean up
    free(safe_str1);
    free(safe_str2);
    cmsIT8Free(hIT8);

    return 0;
}