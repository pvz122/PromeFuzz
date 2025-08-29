// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsPipelineEvalFloat at cmslut.c:1455:16 in lcms2.h
// cmsPipelineEvalReverseFloat at cmslut.c:1753:19 in lcms2.h
// cmsPipelineSetSaveAs8bitsFlag at cmslut.c:1637:19 in lcms2.h
// cmsPipelineAlloc at cmslut.c:1377:24 in lcms2.h
// cmsPipelineCat at cmslut.c:1612:20 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsPipelineDup at cmslut.c:1464:24 in lcms2.h
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
#include <stdint.h>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat32Number) * 9) return 0;

    cmsPipeline* pipeline = cmsPipelineAlloc(nullptr, 3, 3);
    if (!pipeline) return 0;

    cmsFloat32Number in[3], out[3], target[3], result[3], hint[3];
    memcpy(in, Data, sizeof(cmsFloat32Number) * 3);
    memcpy(target, Data + sizeof(cmsFloat32Number) * 3, sizeof(cmsFloat32Number) * 3);
    memcpy(hint, Data + sizeof(cmsFloat32Number) * 6, sizeof(cmsFloat32Number) * 3);

    cmsPipelineEvalFloat(in, out, pipeline);
    cmsPipelineEvalReverseFloat(target, result, hint, pipeline);

    cmsPipelineSetSaveAs8bitsFlag(pipeline, true);

    cmsPipeline* pipeline2 = cmsPipelineAlloc(nullptr, 3, 3);
    if (pipeline2) {
        cmsPipelineCat(pipeline, pipeline2);
        cmsPipelineFree(pipeline2);
    }

    cmsPipeline* dupPipeline = cmsPipelineDup(pipeline);
    if (dupPipeline) {
        cmsPipelineFree(dupPipeline);
    }

    cmsPipelineFree(pipeline);
    return 0;
}