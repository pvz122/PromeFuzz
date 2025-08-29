// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsStageAllocToneCurves at cmslut.c:248:21 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsStageNext at cmslut.c:1243:22 in lcms2.h
// cmsStageData at cmslut.c:1233:17 in lcms2.h
// cmsGetStageContextID at cmslut.c:1238:22 in lcms2.h
// cmsStageDup at cmslut.c:1250:21 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsPipelineInsertStage at cmslut.c:1519:15 in lcms2.h
// cmsPipelineGetPtrToLastStage at cmslut.c:1651:21 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_69(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    cmsContext context = cmsCreateContext(NULL, NULL);
    if (!context) {
        return 0;
    }

    cmsStage* stage = cmsStageAllocToneCurves(context, 3, NULL);
    if (!stage) {
        cmsDeleteContext(context);
        return 0;
    }

    // Fuzz cmsStageNext
    cmsStage* nextStage = cmsStageNext(stage);

    // Fuzz cmsStageData
    void* stageData = cmsStageData(stage);

    // Fuzz cmsGetStageContextID
    cmsContext stageContextID = cmsGetStageContextID(stage);

    // Fuzz cmsStageDup
    cmsStage* dupStage = cmsStageDup(stage);
    if (dupStage) {
        cmsStageFree(dupStage);
    }

    // Create a dummy pipeline
    cmsPipeline* pipeline = cmsPipelineAlloc(context, 3, 3);
    if (pipeline) {
        cmsPipelineInsertStage(pipeline, cmsAT_BEGIN, stage);

        // Fuzz cmsPipelineGetPtrToLastStage
        cmsStage* lastStage = cmsPipelineGetPtrToLastStage(pipeline);

        cmsPipelineFree(pipeline);
    } else {
        cmsStageFree(stage);
    }

    cmsDeleteContext(context);
    return 0;
}