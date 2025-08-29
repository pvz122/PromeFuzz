// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tjBufSizeYUV2 at turbojpeg.c:1003:25 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tjAlloc at turbojpeg.c:887:26 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tjCompressFromYUV at turbojpeg.c:1480:15 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1398:15 in turbojpeg.h
// tjBufSize at turbojpeg.c:937:25 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 5) return 0;

    // Initialize TurboJPEG instance
    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    // Randomly choose width and height
    int width = (Data[0] % 64) + 1;
    int height = (Data[1] % 64) + 1;
    int subsamp = Data[2] % 4;
    int jpegQual = Data[3] % 101;
    int flags = Data[4] % 2 ? TJFLAG_NOREALLOC : 0;

    // Calculate YUV buffer size
    size_t yuvSize = tjBufSizeYUV2(width, 1, height, subsamp);
    if (yuvSize == 0) {
        tj3Destroy(handle);
        return 0;
    }

    // Allocate memory for YUV data
    unsigned char *srcBuf = tjAlloc(yuvSize);
    if (!srcBuf) {
        tj3Destroy(handle);
        return 0;
    }

    // Ensure we don't read beyond the input data
    size_t copySize = std::min(Size - 5, yuvSize);
    if (copySize > 0) {
        memcpy(srcBuf, Data + 5, copySize);
    }

    // Compress from YUV
    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    tjCompressFromYUV(handle, srcBuf, width, 1, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    // Compress from YUV Planes
    const unsigned char *srcPlanes[3] = {srcBuf, srcBuf + width * height, srcBuf + width * height * 5 / 4};
    int strides[3] = {width, width / 2, width / 2};
    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, subsamp, &jpegBuf, &jpegSize, jpegQual, flags);

    // Calculate buffer size
    tjBufSize(width, height, subsamp);

    // Cleanup
    tjFree(srcBuf);
    if (jpegBuf) tjFree(jpegBuf);
    tj3Destroy(handle);

    return 0;
}