// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitDecompress at turbojpeg.c:1812:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tj3LoadImage16 at turbojpeg-mp.c:293:21 in turbojpeg.h
// tj3SaveImage16 at turbojpeg-mp.c:442:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tjLoadImage at turbojpeg.c:3108:26 in turbojpeg.h
// tjSaveImage at turbojpeg.c:3129:15 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjDecompress at turbojpeg.c:2112:15 in turbojpeg.h
// tj3Decompress16 at turbojpeg-mp.c:148:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitDecompress();
    if (!handle) return 0;

    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        tjDestroy(handle);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    int width, height, pixelFormat = TJPF_UNKNOWN;
    unsigned short *image16 = tj3LoadImage16(handle, filename, &width, 1, &height, &pixelFormat);
    if (image16) {
        tj3SaveImage16(handle, filename, image16, width, 0, height, pixelFormat);
        tj3Free(image16);
    }

    unsigned char *image8 = tjLoadImage(filename, &width, 1, &height, &pixelFormat, 0);
    if (image8) {
        tjSaveImage(filename, image8, width, 0, height, pixelFormat, 0);
        tjFree(image8);
    }

    unsigned char *jpegBuf = (unsigned char *)Data;
    unsigned long jpegSize = Size;
    unsigned char *dstBuf = (unsigned char *)malloc(width * height * tjPixelSize[pixelFormat]);
    if (dstBuf) {
        tjDecompress(handle, jpegBuf, jpegSize, dstBuf, width, 0, height, tjPixelSize[pixelFormat], 0);
        free(dstBuf);
    }

    unsigned short *dstBuf16 = (unsigned short *)malloc(width * height * sizeof(unsigned short));
    if (dstBuf16) {
        tj3Decompress16(handle, jpegBuf, jpegSize, dstBuf16, width, pixelFormat);
        free(dstBuf16);
    }

    tjDestroy(handle);
    return 0;
}