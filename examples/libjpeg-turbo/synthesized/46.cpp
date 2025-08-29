// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjCompress at turbojpeg.c:1239:15 in turbojpeg.h
// tjTransform at turbojpeg.c:3045:15 in turbojpeg.h
// tj3SetICCProfile at turbojpeg.c:1168:15 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1398:15 in turbojpeg.h
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
#include <turbojpeg.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    int width = 64;
    int height = 64;
    int pitch = width * 3;
    int pixelSize = 3;
    int jpegSubsamp = TJSAMP_420;
    int jpegQual = 75;
    unsigned long compressedSize = 0;
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * pixelSize);
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * pixelSize);
    unsigned char *jpegBuf = nullptr;
    unsigned char *iccBuf = (unsigned char *)malloc(Size);
    memcpy(iccBuf, Data, Size);

    if (!srcBuf || !dstBuf || !iccBuf) {
        free(srcBuf);
        free(dstBuf);
        free(iccBuf);
        tjDestroy(handle);
        return 0;
    }

    // Fuzz tjCompress
    tjCompress(handle, srcBuf, width, pitch, height, pixelSize, dstBuf, &compressedSize, jpegSubsamp, jpegQual, 0);

    // Fuzz tjTransform
    tjtransform transform;
    transform.op = TJXOP_NONE;
    transform.r.x = 0;
    transform.r.y = 0;
    transform.r.w = width;
    transform.r.h = height;
    unsigned char *dstBufs[1] = {dstBuf};
    unsigned long dstSizes[1] = {0};
    tjTransform(handle, dstBuf, compressedSize, 1, dstBufs, dstSizes, &transform, 0);

    // Fuzz tj3SetICCProfile
    tj3SetICCProfile(handle, iccBuf, Size);

    // Fuzz tjCompressFromYUVPlanes
    const unsigned char *srcPlanes[3] = {srcBuf, srcBuf + width * height, srcBuf + width * height * 5 / 4};
    int strides[3] = {width, width / 2, width / 2};
    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, jpegSubsamp, &jpegBuf, &compressedSize, jpegQual, 0);

    free(srcBuf);
    free(dstBuf);
    free(iccBuf);
    if (jpegBuf) tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}