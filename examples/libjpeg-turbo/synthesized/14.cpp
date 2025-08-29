// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:975:18 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3CompressFromYUV8 at turbojpeg.c:1433:15 in turbojpeg.h
// tj3DecompressToYUV8 at turbojpeg.c:2342:15 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2679:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3EncodeYUV8 at turbojpeg.c:1692:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS | TJINIT_DECOMPRESS);
    if (!handle) return 0;

    int width = 64;
    int height = 64;
    int align = 4;
    int subsamp = TJSAMP_420;
    int pixelFormat = TJPF_RGB;

    size_t yuvBufSize = tj3YUVBufSize(width, align, height, subsamp);
    if (yuvBufSize == 0) {
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *yuvBuf = (unsigned char *)malloc(yuvBufSize);
    if (!yuvBuf) {
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;

    tj3CompressFromYUV8(handle, yuvBuf, width, align, height, &jpegBuf, &jpegSize);

    if (jpegBuf && jpegSize > 0) {
        unsigned char *dstBuf = (unsigned char *)malloc(yuvBufSize);
        if (dstBuf) {
            tj3DecompressToYUV8(handle, jpegBuf, jpegSize, dstBuf, align);
            free(dstBuf);
        }

        unsigned char *rgbBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
        if (rgbBuf) {
            tj3DecodeYUV8(handle, yuvBuf, align, rgbBuf, width, 0, height, pixelFormat);
            free(rgbBuf);
        }

        tj3Free(jpegBuf);
    }

    unsigned char *srcBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (srcBuf) {
        tj3EncodeYUV8(handle, srcBuf, width, 0, height, pixelFormat, yuvBuf, align);
        free(srcBuf);
    }

    free(yuvBuf);
    tj3Destroy(handle);
    return 0;
}