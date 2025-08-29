// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// _cmsStageAllocPlaceholder at cmslut.c:31:21 in lcms2_plugin.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsStageNext at cmslut.c:1243:22 in lcms2.h
// cmsStageType at cmslut.c:1228:29 in lcms2.h
// cmsStageDup at cmslut.c:1250:21 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
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
#include <lcms2_plugin.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsStageSignature) + sizeof(cmsUInt32Number) * 2) {
        return 0;
    }

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) {
        return 0;
    }

    cmsStageSignature type = *reinterpret_cast<const cmsStageSignature*>(Data);
    cmsUInt32Number inputChannels = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsStageSignature));
    cmsUInt32Number outputChannels = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsStageSignature) + sizeof(cmsUInt32Number));

    cmsStage* stage = _cmsStageAllocPlaceholder(context, type, inputChannels, outputChannels, nullptr, nullptr, nullptr, nullptr);
    if (!stage) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsStage* nextStage = cmsStageNext(stage);
    cmsStageSignature stageType = cmsStageType(stage);
    cmsStage* dupStage = cmsStageDup(stage);

    if (dupStage) {
        cmsStageFree(dupStage);
    }

    cmsStageFree(stage);
    cmsDeleteContext(context);

    return 0;
}