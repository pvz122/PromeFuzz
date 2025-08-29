// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjPlaneWidth at turbojpeg.c:1087:15 in turbojpeg.h
// tj3YUVPlaneHeight at turbojpeg.c:1095:15 in turbojpeg.h
// tjPlaneHeight at turbojpeg.c:1121:15 in turbojpeg.h
// tj3YUVPlaneWidth at turbojpeg.c:1061:15 in turbojpeg.h
// tjInitDecompress at turbojpeg.c:1812:20 in turbojpeg.h
// tjDecodeYUV at turbojpeg.c:2725:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0;

    int componentID = Data[0] % 3;
    int width = *reinterpret_cast<const int*>(Data + 1);
    int height = *reinterpret_cast<const int*>(Data + 5);
    int subsamp = Data[9] % 6;
    int align = Data[10] % 8;
    int pixelFormat = Data[11] % 12;
    int flags = Data[12] % 256;

    tjPlaneWidth(componentID, width, subsamp);
    tj3YUVPlaneHeight(componentID, height, subsamp);
    tjPlaneHeight(componentID, height, subsamp);
    tj3YUVPlaneWidth(componentID, width, subsamp);

    tjhandle handle = tjInitDecompress();
    if (handle) {
        unsigned char *dstBuf = (unsigned char *)malloc(width * height * 4);
        if (dstBuf) {
            tjDecodeYUV(handle, Data + 16, align, subsamp, dstBuf, width, width * 4, height, pixelFormat, flags);
            free(dstBuf);
        }
        tjDestroy(handle);
    }

    return 0;
}