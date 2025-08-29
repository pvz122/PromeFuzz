// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjCompress2 at turbojpeg.c:1208:15 in turbojpeg.h
// tjDecompress2 at turbojpeg.c:2063:15 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjInitTransform at turbojpeg.c:2752:20 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    int width = 64;
    int height = 64;
    int pitch = width * 3;
    int pixelFormat = TJPF_RGB;
    int jpegSubsamp = TJSAMP_420;
    int jpegQual = 85;
    unsigned char *srcBuf = (unsigned char *)malloc(width * height * 3);
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    if (!srcBuf) {
        tjDestroy(handle);
        return 0;
    }

    memcpy(srcBuf, Data, std::min(Size, (size_t)(width * height * 3)));

    tjCompress2(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize, jpegSubsamp, jpegQual, 0);

    if (jpegBuf && jpegSize > 0) {
        unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);
        if (dstBuf) {
            tjDecompress2(handle, jpegBuf, jpegSize, dstBuf, width, pitch, height, pixelFormat, 0);
            free(dstBuf);
        }
        tjFree(jpegBuf);
    }

    free(srcBuf);
    tjDestroy(handle);

    tjhandle transformHandle = tjInitTransform();
    if (transformHandle) {
        tjDestroy(transformHandle);
    }

    return 0;
}