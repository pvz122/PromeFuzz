// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsStageAllocMatrix at cmslut.c:379:22 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_136(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 3) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsUInt32Number rows = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsUInt32Number cols = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number));
    cmsUInt32Number nChannels = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 2);

    // Limit rows and cols to prevent stack overflow
    rows = rows % 10 + 1;
    cols = cols % 10 + 1;

    std::vector<cmsFloat64Number> matrix(rows * cols);
    std::vector<cmsFloat64Number> offset(rows);  // Fixed: Initialize with rows instead of cols

    if (Size < sizeof(cmsUInt32Number) * 3 + sizeof(cmsFloat64Number) * (rows * cols + rows)) {
        cmsDeleteContext(context);
        return 0;
    }

    memcpy(matrix.data(), Data + sizeof(cmsUInt32Number) * 3, sizeof(cmsFloat64Number) * rows * cols);
    memcpy(offset.data(), Data + sizeof(cmsUInt32Number) * 3 + sizeof(cmsFloat64Number) * rows * cols, sizeof(cmsFloat64Number) * rows);

    cmsStage* matrixStage = cmsStageAllocMatrix(context, rows, cols, matrix.data(), offset.data());
    if (matrixStage) {
        cmsStageOutputChannels(matrixStage);
        cmsStageInputChannels(matrixStage);
        cmsStageFree(matrixStage);
    }

    cmsUInt32Number clutPoints[] = {2, 2, 2};
    cmsUInt32Number inputChan = nChannels % 4;
    cmsUInt32Number outputChan = nChannels % 4;

    std::vector<cmsFloat32Number> table(inputChan * outputChan * 8);
    if (Size < sizeof(cmsUInt32Number) * 3 + sizeof(cmsFloat64Number) * (rows * cols + rows) + sizeof(cmsFloat32Number) * inputChan * outputChan * 8) {
        cmsDeleteContext(context);
        return 0;
    }

    memcpy(table.data(), Data + sizeof(cmsUInt32Number) * 3 + sizeof(cmsFloat64Number) * (rows * cols + rows), sizeof(cmsFloat32Number) * inputChan * outputChan * 8);

    cmsStage* clutStage = cmsStageAllocCLutFloatGranular(context, clutPoints, inputChan, outputChan, table.data());
    if (clutStage) {
        cmsStageOutputChannels(clutStage);
        cmsStageInputChannels(clutStage);
        cmsStageFree(clutStage);
    }

    cmsStage* identityStage = cmsStageAllocIdentity(context, nChannels);
    if (identityStage) {
        cmsStageOutputChannels(identityStage);
        cmsStageInputChannels(identityStage);
        cmsStageFree(identityStage);
    }

    cmsDeleteContext(context);
    return 0;
}