// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// TJBUFSIZE at turbojpeg.c:952:25 in turbojpeg.h
// tjBufSizeYUV at turbojpeg.c:1011:25 in turbojpeg.h
// TJBUFSIZEYUV at turbojpeg.c:1017:25 in turbojpeg.h
// tjBufSize at turbojpeg.c:937:25 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjCompressFromYUVPlanes at turbojpeg.c:1398:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 4 * sizeof(int)) return 0;

    int width = *reinterpret_cast<const int*>(Data);
    int height = *reinterpret_cast<const int*>(Data + sizeof(int));
    int subsamp = *reinterpret_cast<const int*>(Data + 2 * sizeof(int)) % 5;
    int jpegQual = *reinterpret_cast<const int*>(Data + 3 * sizeof(int)) % 101;

    unsigned long bufSize = TJBUFSIZE(width, height);
    unsigned long yuvBufSize = tjBufSizeYUV(width, height, subsamp);
    unsigned long yuvBufSize2 = TJBUFSIZEYUV(width, height, subsamp);
    unsigned long jpegBufSize = tjBufSize(width, height, subsamp);

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;

    const unsigned char *srcPlanes[3] = {nullptr, nullptr, nullptr};
    int strides[3] = {0, 0, 0};

    tjCompressFromYUVPlanes(handle, srcPlanes, width, strides, height, subsamp, &jpegBuf, &jpegSize, jpegQual, 0);

    if (jpegBuf) tjFree(jpegBuf);
    tjDestroy(handle);

    return 0;
}