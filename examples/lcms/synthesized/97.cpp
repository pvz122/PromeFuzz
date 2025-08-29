// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsGetPipelineContextID at cmslut.c:1407:22 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsCreateTransform at cmsxform.c:1348:32 in lcms2.h
// cmsGetTransformContextID at cmsxform.c:1413:22 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsUnregisterPluginsTHR at cmsplugin.c:780:16 in lcms2.h
// cmsCIECAM02Init at cmscam02.c:358:22 in lcms2.h
// cmsCIECAM02Done at cmscam02.c:427:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    // Fuzz cmsDupContext
    cmsContext dupContext = cmsDupContext(context, nullptr);
    if (dupContext) {
        cmsDeleteContext(dupContext);
    }

    // Fuzz cmsGetPipelineContextID
    cmsPipeline* pipeline = cmsPipelineAlloc(context, 3, 3);
    if (pipeline) {
        cmsContext pipelineContext = cmsGetPipelineContextID(pipeline);
        cmsPipelineFree(pipeline);
    }

    // Fuzz cmsGetTransformContextID
    cmsHTRANSFORM transform = cmsCreateTransform(nullptr, 0, nullptr, 0, 0, 0);
    if (transform) {
        cmsContext transformContext = cmsGetTransformContextID(transform);
        cmsDeleteTransform(transform);
    }

    // Fuzz cmsUnregisterPluginsTHR
    cmsUnregisterPluginsTHR(context);

    // Fuzz cmsCIECAM02Init
    cmsViewingConditions vc = {};
    cmsHANDLE ciecam = cmsCIECAM02Init(context, &vc);
    if (ciecam) {
        cmsCIECAM02Done(ciecam);
    }

    cmsDeleteContext(context);
    return 0;
}