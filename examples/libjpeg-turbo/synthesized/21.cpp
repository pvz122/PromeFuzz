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

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    int componentID = Data[0] % 3;
    int width = (Data[1] << 8) | Data[2];
    int height = (Data[3] << 8) | Data[4];
    int subsamp = Data[5] % 4;
    int align = Data[6] % 2;
    int pitch = (Data[7] << 8) | Data[8];
    int pixelFormat = Data[9] % TJ_NUMPF;
    int flags = 0;

    tjPlaneWidth(componentID, width, subsamp);
    tj3YUVPlaneHeight(componentID, height, subsamp);
    tjPlaneHeight(componentID, height, subsamp);
    tj3YUVPlaneWidth(componentID, width, subsamp);

    tjhandle handle = tjInitDecompress();
    if (handle) {
        unsigned char *srcBuf = (unsigned char *)malloc(Size);
        if (srcBuf) {
            memcpy(srcBuf, Data, Size);
            size_t dstBufSize = width * height * tjPixelSize[pixelFormat];
            if (dstBufSize > 0 && dstBufSize <= Size) {
                unsigned char *dstBuf = (unsigned char *)malloc(dstBufSize);
                if (dstBuf) {
                    tjDecodeYUV(handle, srcBuf, align, subsamp, dstBuf, width, pitch, height, pixelFormat, flags);
                    free(dstBuf);
                }
            }
            free(srcBuf);
        }
        tjDestroy(handle);
    }

    return 0;
}