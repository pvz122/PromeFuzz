// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitDecompress at turbojpeg.c:1812:20 in turbojpeg.h
// tjDecompressHeader at turbojpeg.c:1918:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjPlaneHeight at turbojpeg.c:1121:15 in turbojpeg.h
// tjPlaneWidth at turbojpeg.c:1087:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tj3DecompressToYUVPlanes8 at turbojpeg.c:2126:15 in turbojpeg.h
// tjDecompressToYUV2 at turbojpeg.c:2405:15 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2292:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    tjhandle handle = tjInitDecompress();
    if (!handle) return 0;

    int width, height;
    if (tjDecompressHeader(handle, const_cast<unsigned char*>(Data), Size, &width, &height) != 0) {
        tjDestroy(handle);
        return 0;
    }

    unsigned char *dstPlanes[3];
    int strides[3] = {0, 0, 0};
    int subsamp = TJSAMP_420;

    for (int i = 0; i < 3; ++i) {
        dstPlanes[i] = static_cast<unsigned char*>(malloc(tjPlaneHeight(i, height, subsamp) * tjPlaneWidth(i, width, subsamp)));
        if (!dstPlanes[i]) {
            for (int j = 0; j < i; ++j) free(dstPlanes[j]);
            tjDestroy(handle);
            return 0;
        }
    }

    tj3DecompressToYUVPlanes8(handle, Data, Size, dstPlanes, strides);

    unsigned char *dstBuf = static_cast<unsigned char*>(malloc(width * height * 3 / 2));
    if (dstBuf) {
        tjDecompressToYUV2(handle, Data, Size, dstBuf, width, 4, height, 0);
        free(dstBuf);
    }

    tjDecompressToYUVPlanes(handle, Data, Size, dstPlanes, width, strides, height, 0);

    for (int i = 0; i < 3; ++i) {
        free(dstPlanes[i]);
    }

    tjDestroy(handle);
    return 0;
}