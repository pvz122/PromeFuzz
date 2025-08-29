// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3Get at turbojpeg.c:811:15 in turbojpeg.h
// tj3YUVBufSize at turbojpeg.c:975:18 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3CompressFromYUV8 at turbojpeg.c:1433:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3JPEGBufSize at turbojpeg.c:907:18 in turbojpeg.h
// tj3Decompress16 at turbojpeg-mp.c:148:15 in turbojpeg.h
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
#include <turbojpeg.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    // Fuzz tj3Get
    int param = Data[0] % 10; // Arbitrary parameter selection
    tj3Get(handle, param);

    // Fuzz tj3CompressFromYUV8
    int width = 16;
    int height = 16;
    int align = 1;
    size_t yuvSize = tj3YUVBufSize(width, align, height, TJSAMP_444);
    unsigned char *yuvBuf = (unsigned char *)malloc(yuvSize);
    if (!yuvBuf) {
        tj3Destroy(handle);
        return 0;
    }
    memset(yuvBuf, 0, yuvSize);

    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;
    tj3CompressFromYUV8(handle, yuvBuf, width, align, height, &jpegBuf, &jpegSize);
    free(yuvBuf);
    if (jpegBuf) tj3Free(jpegBuf);

    // Fuzz tj3JPEGBufSize
    int jpegSubsamp = Data[0] % 5; // Arbitrary subsampling selection
    tj3JPEGBufSize(width, height, jpegSubsamp);

    // Fuzz tj3Decompress16
    if (Size > 100) { // Ensure enough data for decompression
        unsigned short *dstBuf = (unsigned short *)malloc(width * height * sizeof(unsigned short));
        if (dstBuf) {
            tj3Decompress16(handle, Data, Size, dstBuf, width, TJPF_RGB);
            free(dstBuf);
        }
    }

    tj3Destroy(handle);
    return 0;
}