// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3SetICCProfile at turbojpeg.c:1168:15 in turbojpeg.h
// tj3Transform at turbojpeg.c:2871:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tjGetErrorStr at turbojpeg.c:640:17 in turbojpeg.h
// tjGetErrorStr2 at turbojpeg.c:634:17 in turbojpeg.h
// tj3GetICCProfile at turbojpeg.c:1930:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    // Fuzz tj3SetICCProfile
    tj3SetICCProfile(handle, (unsigned char *)Data, Size);

    // Fuzz tj3Transform
    unsigned char *dstBuf = nullptr;
    size_t dstSize = 0;
    tjtransform transform = {};
    tj3Transform(handle, Data, Size, 1, &dstBuf, &dstSize, &transform);
    if (dstBuf) tj3Free(dstBuf);

    // Fuzz tjGetErrorStr
    tjGetErrorStr();

    // Fuzz tjGetErrorStr2
    tjGetErrorStr2(handle);

    // Fuzz tj3GetICCProfile
    unsigned char *iccBuf = nullptr;
    size_t iccSize = 0;
    tj3GetICCProfile(handle, &iccBuf, &iccSize);
    if (iccBuf) tj3Free(iccBuf);

    tj3Destroy(handle);
    return 0;
}