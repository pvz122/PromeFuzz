// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3Get at turbojpeg.c:811:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:975:18 in turbojpeg.h
// tjAlloc at turbojpeg.c:887:26 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3CompressFromYUV8 at turbojpeg.c:1433:15 in turbojpeg.h
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tjAlloc at turbojpeg.c:887:26 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2292:15 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjLoadImage at turbojpeg.c:3108:26 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
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
#include "turbojpeg.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    int param = Data[0] % 10;
    tj3Get(handle, param);

    int width = 16;
    int height = 16;
    int align = 1;
    size_t yuvSize = tj3YUVBufSize(width, align, height, TJSAMP_420);
    unsigned char *yuvBuf = (unsigned char *)tjAlloc(yuvSize);
    if (!yuvBuf) {
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;
    tj3CompressFromYUV8(handle, yuvBuf, width, align, height, &jpegBuf, &jpegSize);

    tjhandle decompHandle = tj3Init(TJINIT_DECOMPRESS);
    if (decompHandle && jpegBuf && jpegSize > 0) {
        unsigned char *dstPlanes[3];
        int strides[3] = {width, width / 2, width / 2};
        for (int i = 0; i < 3; i++) {
            dstPlanes[i] = (unsigned char *)tjAlloc(width * height / (i == 0 ? 1 : 2));
        }
        tjDecompressToYUVPlanes(decompHandle, jpegBuf, jpegSize, dstPlanes, width, strides, height, 0);
        for (int i = 0; i < 3; i++) {
            if (dstPlanes[i]) tjFree(dstPlanes[i]);
        }
    }

    if (jpegBuf) tjFree(jpegBuf);
    if (yuvBuf) tjFree(yuvBuf);

    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);

        int width, height, pixelFormat;
        unsigned char *img = tjLoadImage("./dummy_file", &width, 1, &height, &pixelFormat, 0);
        if (img) tjFree(img);
    }

    tj3Destroy(handle);
    if (decompHandle) tj3Destroy(decompHandle);

    return 0;
}