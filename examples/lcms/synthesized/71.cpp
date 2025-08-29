// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsXYZEncoded2Float at cmspcs.c:429:16 in lcms2.h
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsEvalToneCurve16 at cmsgamma.c:1436:27 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsPipelineEval16 at cmslut.c:1447:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// _cmsAdjustEndianess16 at cmsplugin.c:37:28 in lcms2_plugin.h
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
#include <lcms2_plugin.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(cmsUInt16Number)) return 0;

    // Initialize context
    cmsContext context = cmsCreateContext(nullptr, nullptr);

    // Test cmsXYZEncoded2Float
    cmsCIEXYZ fxyz;
    cmsUInt16Number XYZ[3];
    for (int i = 0; i < 3; ++i) {
        XYZ[i] = reinterpret_cast<const cmsUInt16Number*>(Data)[i % (Size / sizeof(cmsUInt16Number))];
    }
    cmsXYZEncoded2Float(&fxyz, XYZ);

    // Test cmsEvalToneCurve16
    cmsUInt16Number v = reinterpret_cast<const cmsUInt16Number*>(Data)[0];
    cmsToneCurve* curve = nullptr;
    if (Size >= 256 * sizeof(cmsUInt16Number)) {
        curve = cmsBuildTabulatedToneCurve16(context, 256, reinterpret_cast<const cmsUInt16Number*>(Data));
    }
    if (curve) {
        cmsEvalToneCurve16(curve, v);
        cmsFreeToneCurve(curve);
    }

    // Test cmsPipelineEval16
    cmsPipeline* pipeline = cmsPipelineAlloc(context, 3, 3);
    if (pipeline) {
        cmsUInt16Number In[3], Out[3];
        for (int i = 0; i < 3; ++i) {
            In[i] = reinterpret_cast<const cmsUInt16Number*>(Data)[i % (Size / sizeof(cmsUInt16Number))];
        }
        cmsPipelineEval16(In, Out, pipeline);
        cmsPipelineFree(pipeline);
    }

    // Test cmsBuildTabulatedToneCurve16
    cmsUInt32Number nEntries = reinterpret_cast<const cmsUInt32Number*>(Data)[0] % 256;
    cmsToneCurve* tabulatedCurve = nullptr;
    if (Size >= nEntries * sizeof(cmsUInt16Number)) {
        tabulatedCurve = cmsBuildTabulatedToneCurve16(context, nEntries, reinterpret_cast<const cmsUInt16Number*>(Data));
    }
    if (tabulatedCurve) {
        cmsFreeToneCurve(tabulatedCurve);
    }

    // Test _cmsAdjustEndianess16
    cmsUInt16Number word = reinterpret_cast<const cmsUInt16Number*>(Data)[0];
    _cmsAdjustEndianess16(word);

    // Cleanup
    cmsDeleteContext(context);

    return 0;
}