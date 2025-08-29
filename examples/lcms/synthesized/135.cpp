// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsStageAllocCLut16bit at cmslut.c:607:21 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsStageAllocCLutFloatGranular at cmslut.c:642:21 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
// cmsStageFree at cmslut.c:1209:16 in lcms2.h
// cmsStageAllocIdentity at cmslut.c:70:21 in lcms2.h
// cmsStageOutputChannels at cmslut.c:1223:28 in lcms2.h
// cmsStageInputChannels at cmslut.c:1218:28 in lcms2.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_135(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 3) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsUInt32Number nGridPoints = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number inputChan = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number outputChan = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 2);

    if (nGridPoints == 0 || inputChan == 0 || outputChan == 0) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsUInt16Number* table = new cmsUInt16Number[nGridPoints * inputChan * outputChan];
    if (!table) {
        cmsDeleteContext(context);
        return 0;
    }

    for (size_t i = 0; i < nGridPoints * inputChan * outputChan; ++i) {
        table[i] = static_cast<cmsUInt16Number>(i % 65536);
    }

    cmsStage* stage = cmsStageAllocCLut16bit(context, nGridPoints, inputChan, outputChan, table);
    if (stage) {
        cmsStageOutputChannels(stage);
        cmsStageInputChannels(stage);
        cmsStageFree(stage);
    }

    delete[] table;

    cmsUInt32Number clutPoints[] = {nGridPoints, nGridPoints, nGridPoints};
    cmsFloat32Number* floatTable = new cmsFloat32Number[nGridPoints * inputChan * outputChan];
    if (!floatTable) {
        cmsDeleteContext(context);
        return 0;
    }

    for (size_t i = 0; i < nGridPoints * inputChan * outputChan; ++i) {
        floatTable[i] = static_cast<cmsFloat32Number>(i) / 65536.0f;
    }

    stage = cmsStageAllocCLutFloatGranular(context, clutPoints, inputChan, outputChan, floatTable);
    if (stage) {
        cmsStageOutputChannels(stage);
        cmsStageInputChannels(stage);
        cmsStageFree(stage);
    }

    delete[] floatTable;

    stage = cmsStageAllocIdentity(context, inputChan);
    if (stage) {
        cmsStageOutputChannels(stage);
        cmsStageInputChannels(stage);
        cmsStageFree(stage);
    }

    cmsDeleteContext(context);
    return 0;
}