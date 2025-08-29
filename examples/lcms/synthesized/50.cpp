// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsWriteUInt32Number at cmsplugin.c:295:20 in lcms2_plugin.h
// _cmsAdjustEndianess32 at cmsplugin.c:58:28 in lcms2_plugin.h
// _cmsEncodeDateTimeNumber at cmsplugin.c:407:16 in lcms2_plugin.h
// _cmsDecodeDateTimeNumber at cmsplugin.c:390:16 in lcms2_plugin.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsGetHeaderCreationDateTime at cmsio0.c:1062:20 in lcms2.h
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
#include <lcms2_plugin.h>
#include <cstdint>
#include <ctime>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 2) return 0;

    // Create a dummy cmsIOHANDLER
    cmsIOHANDLER io = {0};
    io.Write = [](struct _cms_io_handler*, cmsUInt32Number, const void*) -> cmsBool { return TRUE; };

    // Test _cmsWriteUInt32Number
    cmsUInt32Number num = *reinterpret_cast<const cmsUInt32Number*>(Data);
    _cmsWriteUInt32Number(&io, num);

    // Test _cmsAdjustEndianess32
    cmsUInt32Number adjusted = _cmsAdjustEndianess32(num);

    // Test _cmsEncodeDateTimeNumber and _cmsDecodeDateTimeNumber
    struct tm tmSource = {0};
    cmsDateTimeNumber dtNumber;
    _cmsEncodeDateTimeNumber(&dtNumber, &tmSource);

    struct tm tmDest;
    _cmsDecodeDateTimeNumber(&dtNumber, &tmDest);

    // Test cmsGetHeaderCreationDateTime with a valid profile
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (hProfile) {
        struct tm creationTime;
        cmsGetHeaderCreationDateTime(hProfile, &creationTime);
        cmsCloseProfile(hProfile);
    }

    return 0;
}