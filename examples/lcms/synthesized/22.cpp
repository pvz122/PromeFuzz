// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsEstimateGamma at cmsgamma.c:1464:28 in lcms2.h
// cmsSmoothToneCurve at cmsgamma.c:1212:20 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
// cmsBuildParametricToneCurve at cmsgamma.c:880:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
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
#include <stdint.h>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 3 * sizeof(double)) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    double gamma = *reinterpret_cast<const double*>(Data);
    cmsToneCurve* toneCurve = cmsBuildGamma(context, gamma);
    if (!toneCurve) {
        cmsDeleteContext(context);
        return 0;
    }

    double precision = *reinterpret_cast<const double*>(Data + sizeof(double));
    cmsEstimateGamma(toneCurve, precision);

    double lambda = *reinterpret_cast<const double*>(Data + 2 * sizeof(double));
    cmsSmoothToneCurve(toneCurve, lambda);

    cmsToneCurve* triple[3] = {toneCurve, nullptr, nullptr};
    cmsFreeToneCurveTriple(triple);

    if (Size >= (4 + 10) * sizeof(double)) {
        int type = *reinterpret_cast<const int*>(Data + 3 * sizeof(double));
        double params[10];
        for (int i = 0; i < 10; ++i) {
            params[i] = *reinterpret_cast<const double*>(Data + (4 + i) * sizeof(double));
        }
        cmsToneCurve* parametricCurve = cmsBuildParametricToneCurve(context, type, params);
        if (parametricCurve) {
            cmsFreeToneCurve(parametricCurve);
        }
    }

    cmsDeleteContext(context);
    return 0;
}