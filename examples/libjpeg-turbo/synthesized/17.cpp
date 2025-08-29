// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1398:15 in turbojpeg.h
// tjBufSizeYUV2 at turbojpeg.c:1003:25 in turbojpeg.h
// tjEncodeYUV2 at turbojpeg.c:1762:15 in turbojpeg.h
// tjDecodeYUV at turbojpeg.c:2725:15 in turbojpeg.h
// tjEncodeYUVPlanes at turbojpeg.c:1667:15 in turbojpeg.h
// tjDecodeYUVPlanes at turbojpeg.c:2653:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 100) return 0; // Ensure enough data for initialization

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    int width = 64;
    int height = 64;
    int pitch = width * 3;
    int pixelFormat = TJPF_RGB;
    int subsamp = TJSAMP_420;
    int flags = 0;
    int jpegQual = 85;

    unsigned char *srcBuf = (unsigned char *)malloc(width * height * 3);
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    if (!srcBuf || !dstBuf) {
        free(srcBuf);
        free(dstBuf);
        tjDestroy(handle);
        return 0;
    }

    size_t copySize = std::min(Size, static_cast<size_t>(width * height * 3));
    memcpy(srcBuf, Data, copySize);

    // Fuzz tjCompressFromYUVPlanes
    const unsigned char *srcPlanes[3] = {srcBuf, srcBuf + width * height, srcBuf + width * height * 2};
    int strides[3] = {width, width / 2, width / 2};
    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    // Fuzz tjEncodeYUV2
    unsigned char *yuvBuf = (unsigned char *)malloc(tjBufSizeYUV2(width, pitch, height, subsamp));
    if (yuvBuf) {
        tjEncodeYUV2(handle, srcBuf, width, pitch, height, pixelFormat, yuvBuf, subsamp, flags);
        free(yuvBuf);
    }

    // Fuzz tjDecodeYUV
    tjDecodeYUV(handle, srcBuf, 4, subsamp, dstBuf, width, pitch, height, pixelFormat, flags);

    // Fuzz tjEncodeYUVPlanes
    unsigned char *dstPlanes[3];
    int planeStrides[3] = {width, width / 2, width / 2};
    dstPlanes[0] = (unsigned char *)malloc(width * height);
    dstPlanes[1] = (unsigned char *)malloc(width * height / 4);
    dstPlanes[2] = (unsigned char *)malloc(width * height / 4);
    if (dstPlanes[0] && dstPlanes[1] && dstPlanes[2]) {
        tjEncodeYUVPlanes(handle, srcBuf, width, pitch, height, pixelFormat, dstPlanes, planeStrides, subsamp, flags);
        free(dstPlanes[0]);
        free(dstPlanes[1]);
        free(dstPlanes[2]);
    }

    // Fuzz tjDecodeYUVPlanes
    const unsigned char *yuvPlanes[3] = {srcBuf, srcBuf + width * height, srcBuf + width * height * 2};
    tjDecodeYUVPlanes(handle, yuvPlanes, planeStrides, subsamp, dstBuf, width, pitch, height, pixelFormat, flags);

    if (jpegBuf) tjFree(jpegBuf);
    free(srcBuf);
    free(dstBuf);
    tjDestroy(handle);

    return 0;
}