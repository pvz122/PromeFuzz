// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsGBDAlloc at cmssm.c:302:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsGDBAddPoint at cmssm.c:358:19 in lcms2.h
// cmsGDBCheckPoint at cmssm.c:390:19 in lcms2.h
// cmsGDBCompute at cmssm.c:550:19 in lcms2.h
// cmsGBDFree at cmssm.c:313:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIELab)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) {
        return 0;
    }

    cmsHANDLE hGBD = cmsGBDAlloc(context);
    if (!hGBD) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsCIELab lab;
    memcpy(&lab, Data, sizeof(cmsCIELab));

    cmsGDBAddPoint(hGBD, &lab);
    cmsGDBCheckPoint(hGBD, &lab);
    cmsGDBCompute(hGBD, 0);

    cmsGBDFree(hGBD);
    cmsDeleteContext(context);

    return 0;
}