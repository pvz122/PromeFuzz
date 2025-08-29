// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:975:18 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tjEncodeYUV3 at turbojpeg.c:1738:15 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:647:15 in turbojpeg.h
// tjDecodeYUV at turbojpeg.c:2725:15 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:647:15 in turbojpeg.h
// tjCompressFromYUV at turbojpeg.c:1480:15 in turbojpeg.h
// tj3GetErrorCode at turbojpeg.c:647:15 in turbojpeg.h
// tj3CompressFromYUVPlanes8 at turbojpeg.c:1263:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    int width = 16;
    int height = 16;
    int pitch = width * 3;
    int pixelFormat = TJPF_RGB;
    int subsamp = TJSAMP_420;
    int align = 1;
    int flags = 0;
    int jpegQual = 85;

    unsigned char *srcBuf = (unsigned char *)malloc(width * height * 3);
    unsigned char *dstBuf = (unsigned char *)malloc(tj3YUVBufSize(width, align, height, subsamp));
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    if (!srcBuf || !dstBuf) {
        free(srcBuf);
        free(dstBuf);
        tj3Destroy(handle);
        return 0;
    }

    memcpy(srcBuf, Data, std::min(Size, (size_t)(width * height * 3)));

    tjEncodeYUV3(handle, srcBuf, width, pitch, height, pixelFormat, dstBuf, align, subsamp, flags);
    tj3GetErrorCode(handle);

    tjDecodeYUV(handle, dstBuf, align, subsamp, srcBuf, width, pitch, height, pixelFormat, flags);
    tj3GetErrorCode(handle);

    tjCompressFromYUV(handle, dstBuf, width, align, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);
    tj3GetErrorCode(handle);

    const unsigned char *srcPlanes[3] = {dstBuf, dstBuf + width * height, dstBuf + width * height * 5 / 4};
    int strides[3] = {width, width / 2, width / 2};
    tj3CompressFromYUVPlanes8(handle, srcPlanes, width, strides, height, &jpegBuf, &jpegSize);

    tj3Free(jpegBuf);
    free(srcBuf);
    free(dstBuf);
    tj3Destroy(handle);

    return 0;
}