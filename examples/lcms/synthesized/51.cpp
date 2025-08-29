// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsPipelineInputChannels at cmslut.c:1413:27 in lcms2.h
// cmsPipelineOutputChannels at cmslut.c:1419:27 in lcms2.h
// cmsPipelineStageCount at cmslut.c:1661:27 in lcms2.h
// cmsPipelineDup at cmslut.c:1464:24 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
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
#include <stddef.h>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 2) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsUInt32Number inputChannels = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number outputChannels = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));

    cmsPipeline* pipeline = cmsPipelineAlloc(context, inputChannels, outputChannels);
    if (pipeline) {
        cmsPipelineInputChannels(pipeline);
        cmsPipelineOutputChannels(pipeline);
        cmsPipelineStageCount(pipeline);

        cmsPipeline* dupPipeline = cmsPipelineDup(pipeline);
        if (dupPipeline) {
            cmsPipelineFree(dupPipeline);
        }

        cmsPipelineFree(pipeline);
    }

    cmsDeleteContext(context);
    return 0;
}