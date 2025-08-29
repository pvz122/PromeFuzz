// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1985:15 in turbojpeg.h
// tj3DecompressHeader at turbojpeg.c:1819:15 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tjDecompress at turbojpeg.c:2112:15 in turbojpeg.h
// tjDecompress2 at turbojpeg.c:2063:15 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Decompress16 at turbojpeg-mp.c:148:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    tjscalingfactor scalingFactor;
    scalingFactor.num = 1;
    scalingFactor.denom = 2;

    tj3SetScalingFactor(handle, scalingFactor);

    int width = 0, height = 0, pixelFormat = TJPF_RGB;
    tj3DecompressHeader(handle, Data, Size);

    width = 640;
    height = 480;

    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (!dstBuf) {
        tj3Destroy(handle);
        return 0;
    }

    tjDecompress(handle, const_cast<unsigned char *>(Data), Size, dstBuf, width, 0, height, tjPixelSize[pixelFormat], 0);

    tjDecompress2(handle, Data, Size, dstBuf, width, 0, height, pixelFormat, 0);

    unsigned short *dstBuf16 = (unsigned short *)malloc(width * height * sizeof(unsigned short));
    if (!dstBuf16) {
        free(dstBuf);
        tj3Destroy(handle);
        return 0;
    }

    tj3Decompress16(handle, Data, Size, dstBuf16, width, pixelFormat);

    free(dstBuf);
    free(dstBuf16);
    tj3Destroy(handle);

    return 0;
}