// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsCreateLinearizationDeviceLinkTHR at cmsvirt.c:288:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateLinearizationDeviceLink at cmsvirt.c:340:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsReverseToneCurve at cmsgamma.c:1137:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt16Number) * 256 * 3) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsToneCurve* curves[3];
    for (int i = 0; i < 3; ++i) {
        cmsUInt16Number* table = new cmsUInt16Number[256];
        for (int j = 0; j < 256; ++j) {
            table[j] = reinterpret_cast<const cmsUInt16Number*>(Data)[i * 256 + j];
        }
        curves[i] = cmsBuildTabulatedToneCurve16(context, 256, table);
        delete[] table;
    }

    cmsHPROFILE profile1 = cmsCreateLinearizationDeviceLinkTHR(context, cmsSigRgbData, curves);
    if (profile1) cmsCloseProfile(profile1);

    cmsHPROFILE profile2 = cmsCreateLinearizationDeviceLink(cmsSigRgbData, curves);
    if (profile2) cmsCloseProfile(profile2);

    for (int i = 0; i < 3; ++i) {
        cmsToneCurve* reversed = cmsReverseToneCurve(curves[i]);
        if (reversed) cmsFreeToneCurve(reversed);

        cmsToneCurve* dup = cmsDupToneCurve(curves[i]);
        if (dup) cmsFreeToneCurve(dup);
    }

    cmsFreeToneCurveTriple(curves);
    cmsDeleteContext(context);

    return 0;
}