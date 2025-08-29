// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3GetScalingFactors at turbojpeg.c:1963:28 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1985:15 in turbojpeg.h
// tj3SetCroppingRegion at turbojpeg.c:2010:15 in turbojpeg.h
// tj3DecompressHeader at turbojpeg.c:1819:15 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "turbojpeg.h"
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    int numScalingFactors;
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
    if (scalingFactors && numScalingFactors > 0) {
        tj3SetScalingFactor(handle, scalingFactors[Data[0] % numScalingFactors]);
    }

    tjregion croppingRegion;
    croppingRegion.x = Data[0] % 100;
    croppingRegion.y = Data[1] % 100;
    croppingRegion.w = Data[2] % 100;
    croppingRegion.h = Data[3] % 100;
    tj3SetCroppingRegion(handle, croppingRegion);

    if (Size > 0) {
        tj3DecompressHeader(handle, Data, Size);
    }

    tj3Destroy(handle);
    return 0;
}