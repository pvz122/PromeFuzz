// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsIT8SetDataFormat at cmscgats.c:1689:19 in lcms2.h
// cmsIT8GetPatchByName at cmscgats.c:2969:15 in lcms2.h
// cmsIT8SetComment at cmscgats.c:1517:19 in lcms2.h
// cmsIT8SetPropertyStr at cmscgats.c:1528:19 in lcms2.h
// cmsIT8SetPropertyMulti at cmscgats.c:1565:19 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
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
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_113(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext ctx = cmsCreateContext(nullptr, nullptr);
    if (!ctx) return 0;

    cmsHANDLE hIT8 = cmsIT8Alloc(ctx);
    if (!hIT8) {
        cmsDeleteContext(ctx);
        return 0;
    }

    // Generate a dummy string from the input data
    char *dummyStr = new char[Size + 1];
    std::memcpy(dummyStr, Data, Size);
    dummyStr[Size] = '\0';

    // Fuzz cmsIT8SetDataFormat
    cmsIT8SetDataFormat(hIT8, 0, dummyStr);

    // Fuzz cmsIT8GetPatchByName
    cmsIT8GetPatchByName(hIT8, dummyStr);

    // Fuzz cmsIT8SetComment
    cmsIT8SetComment(hIT8, dummyStr);

    // Fuzz cmsIT8SetPropertyStr
    cmsIT8SetPropertyStr(hIT8, dummyStr, dummyStr);

    // Fuzz cmsIT8SetPropertyMulti
    cmsIT8SetPropertyMulti(hIT8, dummyStr, dummyStr, dummyStr);

    delete[] dummyStr;
    cmsIT8Free(hIT8);
    cmsDeleteContext(ctx);

    return 0;
}