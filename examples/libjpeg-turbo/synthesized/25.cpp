// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjCompress2 at turbojpeg.c:1208:15 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjCompress at turbojpeg.c:1239:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjEncodeYUV3 at turbojpeg.c:1738:15 in turbojpeg.h
// tjCompressFromYUV at turbojpeg.c:1480:15 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjEncodeYUVPlanes at turbojpeg.c:1667:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    int width = 64;
    int height = 64;
    int pitch = width * 3;
    int pixelFormat = TJPF_RGB;
    int jpegSubsamp = TJSAMP_420;
    int jpegQual = 85;
    int flags = 0;

    unsigned char *srcBuf = (unsigned char *)malloc(width * height * 3);
    if (!srcBuf) {
        tjDestroy(handle);
        return 0;
    }
    memcpy(srcBuf, Data, std::min(Size, (size_t)(width * height * 3)));

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    tjCompress2(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize, jpegSubsamp, jpegQual, flags);

    if (jpegBuf) tjFree(jpegBuf);

    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);
    if (!dstBuf) {
        free(srcBuf);
        tjDestroy(handle);
        return 0;
    }

    unsigned long compressedSize = 0;
    tjCompress(handle, srcBuf, width, pitch, height, 3, dstBuf, &compressedSize, jpegSubsamp, jpegQual, flags);

    free(dstBuf);

    unsigned char *yuvBuf = (unsigned char *)malloc(width * height * 3 / 2);
    if (!yuvBuf) {
        free(srcBuf);
        tjDestroy(handle);
        return 0;
    }

    tjEncodeYUV3(handle, srcBuf, width, pitch, height, pixelFormat, yuvBuf, 4, jpegSubsamp, flags);

    free(yuvBuf);

    unsigned char *jpegBuf2 = nullptr;
    unsigned long jpegSize2 = 0;

    tjCompressFromYUV(handle, srcBuf, width, 4, height, jpegSubsamp, &jpegBuf2, &jpegSize2, jpegQual, flags);

    if (jpegBuf2) tjFree(jpegBuf2);

    unsigned char *dstPlanes[3];
    int strides[3] = {width, width / 2, width / 2};
    for (int i = 0; i < 3; i++) {
        dstPlanes[i] = (unsigned char *)malloc(width * height / (i == 0 ? 1 : 2));
        if (!dstPlanes[i]) {
            for (int j = 0; j < i; j++) free(dstPlanes[j]);
            free(srcBuf);
            tjDestroy(handle);
            return 0;
        }
    }

    tjEncodeYUVPlanes(handle, srcBuf, width, pitch, height, pixelFormat, dstPlanes, strides, jpegSubsamp, flags);

    for (int i = 0; i < 3; i++) free(dstPlanes[i]);

    free(srcBuf);
    tjDestroy(handle);

    return 0;
}