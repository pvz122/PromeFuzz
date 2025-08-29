// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8EnumDataFormat at cmscgats.c:2645:15 in lcms2.h
// cmsIT8SetDataFormat at cmscgats.c:1689:19 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_121(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHANDLE hIT8 = cmsIT8Alloc(nullptr);
    if (!hIT8) return 0;

    // Fuzz cmsIT8EnumDataFormat
    char **SampleNames = nullptr;
    cmsIT8EnumDataFormat(hIT8, &SampleNames);

    // Fuzz cmsIT8SetDataFormat
    int n = Data[0] % 10;
    const char *Sample = "SampleFormat";
    cmsIT8SetDataFormat(hIT8, n, Sample);

    // Fuzz cmsIT8SetComment
    const char *cComment = "TestComment";
    cmsIT8SetComment(hIT8, cComment);

    // Fuzz cmsIT8SetPropertyStr
    const char *cProp = "TestProperty";
    const char *Str = "TestValue";
    cmsIT8SetPropertyStr(hIT8, cProp, Str);

    // Fuzz cmsIT8SetPropertyMulti
    const char *Key = "TestKey";
    const char *SubKey = "TestSubKey";
    const char *Buffer = "TestBuffer";
    cmsIT8SetPropertyMulti(hIT8, Key, SubKey, Buffer);

    cmsIT8Free(hIT8);
    return 0;
}