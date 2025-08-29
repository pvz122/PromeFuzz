// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3YUVBufSize at turbojpeg.c:975:18 in turbojpeg.h
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3EncodeYUV8 at turbojpeg.c:1692:15 in turbojpeg.h
// tj3CompressFromYUV8 at turbojpeg.c:1433:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    int width = 64;
    int height = 64;
    if (Size < width * height * tjPixelSize[TJPF_RGB]) return 0;

    int align = 1;
    int subsamp = TJSAMP_420;
    int pixelFormat = TJPF_RGB;
    int pitch = width * tjPixelSize[pixelFormat];

    size_t yuvBufSize = tj3YUVBufSize(width, align, height, subsamp);
    if (yuvBufSize == 0) return 0;

    unsigned char *yuvBuf = (unsigned char *)malloc(yuvBufSize);
    if (!yuvBuf) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) {
        free(yuvBuf);
        return 0;
    }

    tj3Set(handle, TJPARAM_SUBSAMP, subsamp);
    tj3Set(handle, TJPARAM_QUALITY, 85);

    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    if (tj3EncodeYUV8(handle, Data, width, pitch, height, pixelFormat, yuvBuf, align) == 0) {
        tj3CompressFromYUV8(handle, yuvBuf, width, align, height, &jpegBuf, &jpegSize);
    }

    tj3Free(yuvBuf);
    tj3Free(jpegBuf);
    tj3Destroy(handle);

    return 0;
}