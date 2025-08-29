// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitDecompress at turbojpeg.c:1812:20 in turbojpeg.h
// tjDecompressHeader3 at turbojpeg.c:1878:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjDecompress at turbojpeg.c:2112:15 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2292:15 in turbojpeg.h
// tjBufSizeYUV2 at turbojpeg.c:1003:25 in turbojpeg.h
// tjDecompressToYUV at turbojpeg.c:2453:15 in turbojpeg.h
// tjDecompressToYUV2 at turbojpeg.c:2405:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitDecompress();
    if (!handle) return 0;

    int width = 0, height = 0, jpegSubsamp = 0, jpegColorspace = 0;
    if (tjDecompressHeader3(handle, const_cast<unsigned char*>(Data), Size, &width, &height, &jpegSubsamp, &jpegColorspace) != 0) {
        tjDestroy(handle);
        return 0;
    }

    unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);
    if (!dstBuf) {
        tjDestroy(handle);
        return 0;
    }

    tjDecompress(handle, const_cast<unsigned char*>(Data), Size, dstBuf, width, 0, height, 3, 0);

    unsigned char *dstPlanes[3];
    int strides[3];
    for (int i = 0; i < 3; i++) {
        dstPlanes[i] = (unsigned char *)malloc(width * height);
        strides[i] = width;
    }

    tjDecompressToYUVPlanes(handle, const_cast<unsigned char*>(Data), Size, dstPlanes, width, strides, height, 0);

    unsigned char *dstYUV = (unsigned char *)malloc(tjBufSizeYUV2(width, 1, height, jpegSubsamp));
    if (dstYUV) {
        tjDecompressToYUV(handle, const_cast<unsigned char*>(Data), Size, dstYUV, 0);
        tjDecompressToYUV2(handle, const_cast<unsigned char*>(Data), Size, dstYUV, width, 1, height, 0);
        free(dstYUV);
    }

    free(dstBuf);
    for (int i = 0; i < 3; i++) {
        free(dstPlanes[i]);
    }

    tjDestroy(handle);
    return 0;
}