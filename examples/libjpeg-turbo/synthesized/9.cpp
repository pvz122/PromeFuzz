// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjBufSizeYUV at turbojpeg.c:1011:25 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjEncodeYUV at turbojpeg.c:1771:15 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1398:15 in turbojpeg.h
// tjEncodeYUV2 at turbojpeg.c:1762:15 in turbojpeg.h
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
#include "turbojpeg.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    int width = 64;
    int height = 64;
    int pitch = width * 3;
    int pixelSize = 3;
    int subsamp = TJSAMP_420;
    int flags = 0;
    int jpegQual = 85;

    unsigned char *srcBuf = (unsigned char *)malloc(width * height * pixelSize);
    unsigned char *dstBuf = (unsigned char *)malloc(tjBufSizeYUV(width, height, subsamp));
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    const unsigned char *srcPlanes[3];
    int strides[3];
    unsigned char *dstPlanes[3];

    if (!srcBuf || !dstBuf) {
        free(srcBuf);
        free(dstBuf);
        tjDestroy(handle);
        return 0;
    }

    memcpy(srcBuf, Data, std::min(Size, (size_t)(width * height * pixelSize)));

    tjEncodeYUV(handle, srcBuf, width, pitch, height, pixelSize, dstBuf, subsamp, flags);
    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);
    tjEncodeYUV2(handle, srcBuf, width, pitch, height, TJPF_RGB, dstBuf, subsamp, flags);
    tjEncodeYUVPlanes(handle, srcBuf, width, pitch, height, TJPF_RGB, dstPlanes, strides, subsamp, flags);
    tjDecodeYUVPlanes(handle, srcPlanes, strides, subsamp, dstBuf, width, pitch, height, TJPF_RGB, flags);

    free(srcBuf);
    free(dstBuf);
    if (jpegBuf) tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}