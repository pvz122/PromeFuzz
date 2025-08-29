// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsStageAllocCLutFloat at cmslut.c:624:21 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocCLut16bit at cmslut.c:607:21 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocCLutFloatGranular at cmslut.c:642:21 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocCLut16bitGranular at cmslut.c:547:21 in lcms2.h
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
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsUInt32Number nGridPoints = *reinterpret_cast<const cmsUInt32Number*>(Data);
    if (nGridPoints == 0) nGridPoints = 1; // Ensure nGridPoints is at least 1
    cmsUInt32Number inputChan = 3;
    cmsUInt32Number outputChan = 3;

    // Allocate memory for tables
    size_t tableSizeFloat = nGridPoints * inputChan * outputChan * sizeof(cmsFloat32Number);
    size_t tableSize16Bit = nGridPoints * inputChan * outputChan * sizeof(cmsUInt16Number);
    if (Size < 4 + tableSizeFloat + tableSize16Bit) {
        cmsDeleteContext(context);
        return 0;
    }

    const cmsFloat32Number* tableFloat = reinterpret_cast<const cmsFloat32Number*>(Data + 4);
    const cmsUInt16Number* table16Bit = reinterpret_cast<const cmsUInt16Number*>(Data + 4 + tableSizeFloat);

    // Test cmsStageAllocCLutFloat
    cmsStage* stageFloat = cmsStageAllocCLutFloat(context, nGridPoints, inputChan, outputChan, tableFloat);
    if (stageFloat) cmsStageFree(stageFloat);

    // Test cmsStageAllocCLut16bit
    cmsStage* stage16Bit = cmsStageAllocCLut16bit(context, nGridPoints, inputChan, outputChan, table16Bit);
    if (stage16Bit) cmsStageFree(stage16Bit);

    // Test cmsStageAllocCLutFloatGranular
    cmsUInt32Number clutPoints[] = {nGridPoints, nGridPoints, nGridPoints};
    cmsStage* stageFloatGranular = cmsStageAllocCLutFloatGranular(context, clutPoints, inputChan, outputChan, tableFloat);
    if (stageFloatGranular) cmsStageFree(stageFloatGranular);

    // Test cmsStageAllocIdentity
    cmsStage* stageIdentity = cmsStageAllocIdentity(context, inputChan);
    if (stageIdentity) cmsStageFree(stageIdentity);

    // Test cmsStageAllocCLut16bitGranular
    cmsStage* stage16BitGranular = cmsStageAllocCLut16bitGranular(context, clutPoints, inputChan, outputChan, table16Bit);
    if (stage16BitGranular) cmsStageFree(stage16BitGranular);

    cmsDeleteContext(context);
    return 0;
}