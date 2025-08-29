// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:975:18 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3CompressFromYUV8 at turbojpeg.c:1433:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3DecodeYUV8 at turbojpeg.c:2679:15 in turbojpeg.h
// tj3EncodeYUV8 at turbojpeg.c:1692:15 in turbojpeg.h
// tj3EncodeYUVPlanes8 at turbojpeg.c:1512:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS | TJINIT_DECOMPRESS);
    if (!handle) return 0;

    int width = *(reinterpret_cast<const int*>(Data));
    int height = *(reinterpret_cast<const int*>(Data + 4));
    int align = *(reinterpret_cast<const int*>(Data + 8));
    int subsamp = *(reinterpret_cast<const int*>(Data + 12)) % 5;

    size_t yuvSize = tj3YUVBufSize(width, align, height, subsamp);
    if (yuvSize == 0) {
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *yuvBuf = static_cast<unsigned char*>(malloc(yuvSize));
    if (!yuvBuf) {
        tj3Destroy(handle);
        return 0;
    }

    memcpy(yuvBuf, Data + 16, Size - 16 < yuvSize ? Size - 16 : yuvSize);

    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;
    tj3CompressFromYUV8(handle, yuvBuf, width, align, height, &jpegBuf, &jpegSize);

    if (jpegBuf) tj3Free(jpegBuf);

    unsigned char *dstBuf = static_cast<unsigned char*>(malloc(width * height * 3));
    if (dstBuf) {
        tj3DecodeYUV8(handle, yuvBuf, align, dstBuf, width, width * 3, height, TJPF_RGB);
        free(dstBuf);
    }

    unsigned char *dstYUVBuf = static_cast<unsigned char*>(malloc(yuvSize));
    if (dstYUVBuf) {
        tj3EncodeYUV8(handle, yuvBuf, width, width * 3, height, TJPF_RGB, dstYUVBuf, align);
        free(dstYUVBuf);
    }

    unsigned char *dstPlanes[3];
    int strides[3] = {0, 0, 0};
    dstPlanes[0] = static_cast<unsigned char*>(malloc(width * height));
    dstPlanes[1] = static_cast<unsigned char*>(malloc(width * height / 4));
    dstPlanes[2] = static_cast<unsigned char*>(malloc(width * height / 4));
    if (dstPlanes[0] && dstPlanes[1] && dstPlanes[2]) {
        tj3EncodeYUVPlanes8(handle, yuvBuf, width, width * 3, height, TJPF_RGB, dstPlanes, strides);
        free(dstPlanes[0]);
        free(dstPlanes[1]);
        free(dstPlanes[2]);
    }

    free(yuvBuf);
    tj3Destroy(handle);

    return 0;
}