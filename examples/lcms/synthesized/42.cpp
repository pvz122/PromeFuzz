// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsStageAllocToneCurves at cmslut.c:248:21 in lcms2.h
// cmsPipelineInsertStage at cmslut.c:1519:15 in lcms2.h
// cmsPipelineGetPtrToLastStage at cmslut.c:1651:21 in lcms2.h
// cmsPipelineUnlinkStage at cmslut.c:1555:16 in lcms2.h
// cmsPipelineGetPtrToFirstStage at cmslut.c:1646:21 in lcms2.h
// cmsPipelineDup at cmslut.c:1464:24 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
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
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsContext ctx = cmsCreateContext(nullptr, nullptr);
    cmsPipeline* pipeline = cmsPipelineAlloc(ctx, 3, 3);
    cmsStage* stage = cmsStageAllocToneCurves(ctx, 3, nullptr);

    // Fuzz cmsPipelineInsertStage
    cmsPipelineInsertStage(pipeline, static_cast<cmsStageLoc>(Data[0] % 2), stage);

    // Fuzz cmsPipelineGetPtrToLastStage
    cmsStage* lastStage = cmsPipelineGetPtrToLastStage(pipeline);

    // Fuzz cmsPipelineUnlinkStage
    cmsStage* unlinkedStage = nullptr;
    cmsPipelineUnlinkStage(pipeline, static_cast<cmsStageLoc>(Data[0] % 2), &unlinkedStage);

    // Fuzz cmsPipelineGetPtrToFirstStage
    cmsStage* firstStage = cmsPipelineGetPtrToFirstStage(pipeline);

    // Fuzz cmsPipelineDup
    cmsPipeline* dupPipeline = cmsPipelineDup(pipeline);

    if (dupPipeline) cmsPipelineFree(dupPipeline);
    if (unlinkedStage) cmsStageFree(unlinkedStage);
    cmsPipelineFree(pipeline);
    cmsDeleteContext(ctx);

    return 0;
}