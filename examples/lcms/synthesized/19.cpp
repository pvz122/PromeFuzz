// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// _cmsPipelineSetOptimizationParameters at cmslut.c:1674:16 in lcms2_plugin.h
// cmsPipelineSetSaveAs8bitsFlag at cmslut.c:1637:19 in lcms2.h
// cmsPipelineCheckAndRetreiveStages at cmslut.c:110:20 in lcms2.h
// cmsPipelineCat at cmslut.c:1612:20 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsPipeline* pipeline1 = cmsPipelineAlloc(nullptr, 3, 3);
    cmsPipeline* pipeline2 = cmsPipelineAlloc(nullptr, 3, 3);

    if (!pipeline1 || !pipeline2) {
        if (pipeline1) cmsPipelineFree(pipeline1);
        if (pipeline2) cmsPipelineFree(pipeline2);
        return 0;
    }

    cmsUInt32Number* params = (cmsUInt32Number*)Data;
    cmsUInt32Number param1 = params[0];

    _cmsPipelineSetOptimizationParameters(pipeline1, nullptr, nullptr, nullptr, nullptr);
    cmsPipelineSetSaveAs8bitsFlag(pipeline1, param1 % 2);

    cmsStage* stage1 = nullptr;
    cmsStage* stage2 = nullptr;
    cmsPipelineCheckAndRetreiveStages(pipeline1, 0, &stage1, &stage2);

    cmsPipelineCat(pipeline1, pipeline2);

    cmsPipelineFree(pipeline1);
    cmsPipelineFree(pipeline2);

    return 0;
}