// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsStageAllocCLutFloatGranular at cmslut.c:642:21 in lcms2.h
// cmsStageSampleCLutFloat at cmslut.c:813:19 in lcms2.h
// cmsStageSampleCLut16bit at cmslut.c:747:19 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsSliceSpaceFloat at cmslut.c:910:26 in lcms2.h
// cmsSliceSpace16 at cmslut.c:879:19 in lcms2.h
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

static cmsBool FloatSampler(const cmsFloat32Number In[], cmsFloat32Number Out[], void* Cargo) {
    return TRUE;
}

static cmsBool Int16Sampler(const cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo) {
    return TRUE;
}

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 3) return 0;

    cmsContext ContextID = cmsCreateContext(NULL, NULL);
    if (!ContextID) return 0;

    cmsUInt32Number clutPoints[3];
    memcpy(clutPoints, Data, sizeof(clutPoints));
    clutPoints[0] = clutPoints[0] % 3 + 1; // Clamp to max 3
    clutPoints[1] = clutPoints[1] % 3 + 1; // Clamp to max 3
    clutPoints[2] = clutPoints[2] % 3 + 1; // Clamp to max 3

    cmsUInt32Number inputChan = clutPoints[0];
    cmsUInt32Number outputChan = clutPoints[1];

    cmsStage* stage = cmsStageAllocCLutFloatGranular(ContextID, clutPoints, inputChan, outputChan, NULL);
    if (stage) {
        cmsStageSampleCLutFloat(stage, FloatSampler, NULL, 0);
        cmsStageSampleCLut16bit(stage, Int16Sampler, NULL, 0);
        cmsStageFree(stage);
    }

    cmsSliceSpaceFloat(inputChan, clutPoints, FloatSampler, NULL);
    cmsSliceSpace16(inputChan, clutPoints, Int16Sampler, NULL);

    cmsDeleteContext(ContextID);
    return 0;
}