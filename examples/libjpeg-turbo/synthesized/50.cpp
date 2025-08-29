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
#include <turbojpeg.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    // Randomly choose between setting scaling factor or cropping region
    if (Data[0] % 2 == 0) {
        int numScalingFactors;
        const tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
        if (scalingFactors && numScalingFactors > 0) {
            int index = Data[0] % numScalingFactors;
            tj3SetScalingFactor(handle, scalingFactors[index]);
        }
    } else {
        tjregion croppingRegion;
        croppingRegion.x = Data[0] % 100;
        croppingRegion.y = Data[0] % 100;
        croppingRegion.w = Data[0] % 100;
        croppingRegion.h = Data[0] % 100;
        tj3SetCroppingRegion(handle, croppingRegion);
    }

    // Decompress header
    tj3DecompressHeader(handle, Data, Size);

    tj3Destroy(handle);
    return 0;
}