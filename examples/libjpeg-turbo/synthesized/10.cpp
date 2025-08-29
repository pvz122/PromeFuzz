// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1985:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Get at turbojpeg.c:811:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    // Fuzz tj3SetScalingFactor
    tjscalingfactor scalingFactor;
    scalingFactor.num = Data[0];
    scalingFactor.denom = Data[1];
    tj3SetScalingFactor(handle, scalingFactor);

    // Fuzz tj3Set
    int param = Data[2] % 10; // Example: limit param to 0-9
    int value = Data[3];
    tj3Set(handle, param, value);

    // Fuzz tj3Get
    tj3Get(handle, param);

    // Fuzz tj3SetCroppingRegion
    tjregion croppingRegion;
    croppingRegion.x = Data[0];
    croppingRegion.y = Data[1];
    croppingRegion.w = Data[2];
    croppingRegion.h = Data[3];
    tj3SetCroppingRegion(handle, croppingRegion);

    tj3Destroy(handle);
    return 0;
}