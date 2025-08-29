// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3DecompressHeader at turbojpeg.c:1819:15 in turbojpeg.h
// tj3GetScalingFactors at turbojpeg.c:1963:28 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1985:15 in turbojpeg.h
// tj3SetCroppingRegion at turbojpeg.c:2010:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) {
        return 0;
    }

    // Test tj3DecompressHeader
    if (tj3DecompressHeader(handle, Data, Size) == 0) {
        int numScalingFactors;
        tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
        if (scalingFactors && numScalingFactors > 0) {
            // Test tj3SetScalingFactor
            tj3SetScalingFactor(handle, scalingFactors[0]);

            // Test tj3SetCroppingRegion
            tjregion croppingRegion = {0, 0, 100, 100};
            tj3SetCroppingRegion(handle, croppingRegion);
        }
    }

    tj3Destroy(handle);
    return 0;
}