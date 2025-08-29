// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjCompress at turbojpeg.c:1239:15 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1398:15 in turbojpeg.h
// tj3SetICCProfile at turbojpeg.c:1168:15 in turbojpeg.h
// tjTransform at turbojpeg.c:3045:15 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
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
#include "turbojpeg.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    int width = 64;
    int height = 64;
    int pitch = width * 3;
    int pixelSize = 3;
    unsigned long compressedSize = 0;
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * pixelSize);
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * pixelSize);
    if (!srcBuf || !dstBuf) {
        free(srcBuf);
        free(dstBuf);
        tjDestroy(handle);
        return 0;
    }

    memcpy(srcBuf, Data, std::min(Size, (size_t)(width * height * pixelSize)));

    tjCompress(handle, srcBuf, width, pitch, height, pixelSize, dstBuf, &compressedSize, TJSAMP_420, 75, TJFLAG_FASTDCT);

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    const unsigned char *srcPlanes[3] = {srcBuf, srcBuf + width * height, srcBuf + width * height * 5 / 4};
    int strides[3] = {width, width / 2, width / 2};
    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, TJSAMP_420, &jpegBuf, &jpegSize, 75, TJFLAG_FASTDCT);

    unsigned char *iccBuf = (unsigned char *)malloc(Size);
    if (iccBuf) {
        memcpy(iccBuf, Data, Size);
        tj3SetICCProfile(handle, iccBuf, Size);
        free(iccBuf);
    }

    unsigned char *dstBufs[1] = {nullptr};
    unsigned long dstSizes[1] = {0};
    tjtransform transforms[1] = {{{0, 0, width, height}, TJXOP_NONE, 0, nullptr}};
    tjTransform(handle, dstBuf, compressedSize, 1, dstBufs, dstSizes, transforms, TJFLAG_FASTDCT);

    free(srcBuf);
    free(dstBuf);
    if (jpegBuf) tjFree(jpegBuf);
    if (dstBufs[0]) tjFree(dstBufs[0]);
    tjDestroy(handle);

    return 0;
}