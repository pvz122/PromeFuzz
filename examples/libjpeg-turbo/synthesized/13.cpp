// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitDecompress at turbojpeg.c:1812:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tj3DecodeYUVPlanes8 at turbojpeg.c:2512:15 in turbojpeg.h
// tj3GetErrorStr at turbojpeg.c:622:17 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 100) return 0;

    tjhandle handle = tjInitDecompress();
    if (!handle) return 0;

    int width = 64;
    int height = 64;
    int pitch = width * 3;
    int pixelFormat = TJPF_RGB;

    unsigned char *dstBuf = (unsigned char *)malloc(pitch * height);
    if (!dstBuf) {
        tjDestroy(handle);
        return 0;
    }

    const unsigned char *srcPlanes[3];
    int strides[3] = {0, 0, 0};

    srcPlanes[0] = Data;
    srcPlanes[1] = Data + width * height;
    srcPlanes[2] = Data + width * height + (width * height) / 4;

    int result = tj3DecodeYUVPlanes8(handle, srcPlanes, strides, dstBuf, width, pitch, height, pixelFormat);
    if (result == -1) {
        const char *errorStr = tj3GetErrorStr(handle);
    }

    free(dstBuf);
    tjDestroy(handle);

    return 0;
}