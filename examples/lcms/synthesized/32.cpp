// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsLabEncoded2FloatV2 at cmspcs.c:218:16 in lcms2.h
// cmsLabEncoded2FloatV2 at cmspcs.c:218:16 in lcms2.h
// cmsLabEncoded2Float at cmspcs.c:226:16 in lcms2.h
// cmsLabEncoded2Float at cmspcs.c:226:16 in lcms2.h
// cmsFloat2LabEncodedV2 at cmspcs.c:254:16 in lcms2.h
// cmsFloat2LabEncodedV2 at cmspcs.c:254:16 in lcms2.h
// cmsBFDdeltaE at cmspcs.c:497:28 in lcms2.h
// cmsFloat2LabEncoded at cmspcs.c:298:16 in lcms2.h
// cmsFloat2LabEncoded at cmspcs.c:298:16 in lcms2.h
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
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    cmsCIELab Lab1, Lab2;
    cmsUInt16Number wLab1[3], wLab2[3];

    // Initialize wLab1 and wLab2 with fuzz data, ensuring no out-of-bounds access
    for (int i = 0; i < 3; ++i) {
        if (Size >= (i * 2 + 2)) {
            wLab1[i] = (Data[i * 2] << 8) | Data[i * 2 + 1];
        } else {
            wLab1[i] = 0;
        }
        if (Size >= (i * 2 + 5)) {
            wLab2[i] = (Data[i * 2 + 3] << 8) | Data[i * 2 + 4];
        } else {
            wLab2[i] = 0;
        }
    }

    // Test cmsLabEncoded2FloatV2
    cmsLabEncoded2FloatV2(&Lab1, wLab1);
    cmsLabEncoded2FloatV2(&Lab2, wLab2);

    // Test cmsLabEncoded2Float
    cmsLabEncoded2Float(&Lab1, wLab1);
    cmsLabEncoded2Float(&Lab2, wLab2);

    // Test cmsFloat2LabEncodedV2
    cmsFloat2LabEncodedV2(wLab1, &Lab1);
    cmsFloat2LabEncodedV2(wLab2, &Lab2);

    // Test cmsBFDdeltaE
    cmsBFDdeltaE(&Lab1, &Lab2);

    // Test cmsFloat2LabEncoded
    cmsFloat2LabEncoded(wLab1, &Lab1);
    cmsFloat2LabEncoded(wLab2, &Lab2);

    return 0;
}