// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1985:15 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:975:18 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Alloc at turbojpeg.c:881:17 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3DecompressToYUV8 at turbojpeg.c:2342:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Alloc at turbojpeg.c:881:17 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2679:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    tjscalingfactor scalingFactor;
    scalingFactor.num = 1;
    scalingFactor.denom = 2;

    if (tj3SetScalingFactor(handle, scalingFactor) != 0) {
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *jpegBuf = (unsigned char *)Data;
    size_t jpegSize = Size;

    int width = 640;
    int height = 480;
    int align = 4;
    int subsamp = TJSAMP_420;

    size_t yuvBufSize = tj3YUVBufSize(width, align, height, subsamp);
    if (yuvBufSize == 0) {
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *yuvBuf = (unsigned char *)tj3Alloc(yuvBufSize);
    if (!yuvBuf) {
        tj3Destroy(handle);
        return 0;
    }

    if (tj3DecompressToYUV8(handle, jpegBuf, jpegSize, yuvBuf, align) != 0) {
        tj3Free(yuvBuf);
        tj3Destroy(handle);
        return 0;
    }

    int pixelFormat = TJPF_RGB;
    int pitch = width * tjPixelSize[pixelFormat];
    unsigned char *rgbBuf = (unsigned char *)tj3Alloc(pitch * height);
    if (!rgbBuf) {
        tj3Free(yuvBuf);
        tj3Destroy(handle);
        return 0;
    }

    if (tj3DecodeYUV8(handle, yuvBuf, align, rgbBuf, width, pitch, height, pixelFormat) != 0) {
        tj3Free(rgbBuf);
        tj3Free(yuvBuf);
        tj3Destroy(handle);
        return 0;
    }

    tj3Free(rgbBuf);
    tj3Free(yuvBuf);
    tj3Destroy(handle);

    return 0;
}