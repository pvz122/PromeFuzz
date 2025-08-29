// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjCompress at turbojpeg.c:1239:15 in turbojpeg.h
// tjTransform at turbojpeg.c:3045:15 in turbojpeg.h
// tj3SetICCProfile at turbojpeg.c:1168:15 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1398:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Randomly generate parameters for tjCompress
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

    tjCompress(handle, srcBuf, width, pitch, height, pixelSize, dstBuf, &compressedSize, TJSAMP_420, 75, 0);

    // Randomly generate parameters for tjTransform
    unsigned char *jpegBuf = dstBuf;
    unsigned long jpegSize = compressedSize;
    unsigned char *dstBufs[1];
    unsigned long dstSizes[1];
    tjtransform transforms[1];
    transforms[0].r.x = 0;
    transforms[0].r.y = 0;
    transforms[0].r.w = width;
    transforms[0].r.h = height;
    transforms[0].op = TJXOP_NONE;
    transforms[0].data = nullptr;
    transforms[0].customFilter = nullptr;

    tjTransform(handle, jpegBuf, jpegSize, 1, dstBufs, dstSizes, transforms, 0);

    // Randomly generate parameters for tj3SetICCProfile
    unsigned char *iccBuf = (unsigned char *)malloc(Size);
    if (iccBuf) {
        memcpy(iccBuf, Data, Size);
        tj3SetICCProfile(handle, iccBuf, Size);
        free(iccBuf);
    }

    // Randomly generate parameters for tjCompressFromYUVPlanes
    const unsigned char *srcPlanes[3];
    int strides[3];
    srcPlanes[0] = srcBuf;
    srcPlanes[1] = srcBuf + width * height;
    srcPlanes[2] = srcBuf + width * height * 2;
    strides[0] = width;
    strides[1] = width / 2;
    strides[2] = width / 2;

    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, TJSAMP_420, &dstBuf, &jpegSize, 75, 0);

    free(srcBuf);
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}