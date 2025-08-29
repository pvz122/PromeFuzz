// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8SetDataFormat at cmscgats.c:1689:19 in lcms2.h
// cmsIT8SetPropertyHex at cmscgats.c:1548:19 in lcms2.h
// cmsIT8SetComment at cmscgats.c:1517:19 in lcms2.h
// cmsIT8SetPropertyStr at cmscgats.c:1528:19 in lcms2.h
// cmsIT8SetPropertyMulti at cmscgats.c:1565:19 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_115(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHANDLE hIT8 = cmsIT8Alloc(nullptr);
    if (!hIT8) return 0;

    // Use the first byte to determine which function to fuzz
    uint8_t functionSelector = Data[0] % 5;
    Data++;
    Size--;

    // Ensure Data is null-terminated for string operations
    std::vector<char> buffer(Size + 1);
    if (Size > 0) {
        memcpy(buffer.data(), Data, Size);
    }
    buffer[Size] = '\0';

    switch (functionSelector) {
        case 0: {
            // cmsIT8SetDataFormat
            int n = Size > 0 ? Data[0] : 0;
            const char* Sample = buffer.data();
            cmsIT8SetDataFormat(hIT8, n, Sample);
            break;
        }
        case 1: {
            // cmsIT8SetPropertyHex
            const char* cProp = "PropertyHex";
            cmsUInt32Number Val = Size > 0 ? Data[0] : 0;
            cmsIT8SetPropertyHex(hIT8, cProp, Val);
            break;
        }
        case 2: {
            // cmsIT8SetComment
            const char* cComment = buffer.data();
            cmsIT8SetComment(hIT8, cComment);
            break;
        }
        case 3: {
            // cmsIT8SetPropertyStr
            const char* cProp = "PropertyStr";
            const char* Str = buffer.data();
            cmsIT8SetPropertyStr(hIT8, cProp, Str);
            break;
        }
        case 4: {
            // cmsIT8SetPropertyMulti
            const char* Key = "Key";
            const char* SubKey = "SubKey";
            const char* Buffer = buffer.data();
            cmsIT8SetPropertyMulti(hIT8, Key, SubKey, Buffer);
            break;
        }
        default:
            break;
    }

    cmsIT8Free(hIT8);
    return 0;
}