// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsSliceSpace16 at cmslut.c:879:19 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsFormatterForColorspaceOfProfile at cmspack.c:4025:27 in lcms2.h
// cmsIsCLUT at cmsio1.c:830:20 in lcms2.h
// cmsIsIntentSupported at cmsio1.c:864:20 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsStageAllocCLutFloatGranular at cmslut.c:642:21 in lcms2.h
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
#include <string.h>

static cmsBool Sampler16(const cmsUInt16Number In[], cmsUInt16Number Out[], void* Cargo) {
    return TRUE;
}

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 7) return 0;

    cmsContext ContextID = cmsCreateContext(NULL, NULL);
    if (!ContextID) return 0;

    cmsUInt32Number nInputs = Data[0] % 16;
    cmsUInt32Number clutPoints[16];
    for (int i = 0; i < nInputs; i++) {
        clutPoints[i] = Data[i % Size] % 16 + 1;
    }

    cmsSliceSpace16(nInputs, clutPoints, Sampler16, NULL);

    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (hProfile) {
        cmsFormatterForColorspaceOfProfile(hProfile, Data[1] % 2 + 1, Data[2] % 2);
        cmsIsCLUT(hProfile, Data[3] % 4, Data[4] % 3);
        cmsIsIntentSupported(hProfile, Data[5] % 4, Data[6] % 3);
        cmsCloseProfile(hProfile);
    }

    cmsFloat32Number Table[16 * 16 * 16 * 3];
    for (int i = 0; i < 16 * 16 * 16 * 3; i++) {
        Table[i] = (cmsFloat32Number)Data[i % Size] / 255.0f;
    }

    cmsStage* stage = cmsStageAllocCLutFloatGranular(ContextID, clutPoints, nInputs, 3, Table);
    if (stage) {
        cmsStageFree(stage);
    }

    cmsDeleteContext(ContextID);
    return 0;
}