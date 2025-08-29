// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3TransformBufSize at turbojpeg.c:2832:18 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Alloc at turbojpeg.c:881:17 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Transform at turbojpeg.c:2871:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3TransformBufSize at turbojpeg.c:2832:18 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Alloc at turbojpeg.c:881:17 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Transform at turbojpeg.c:2871:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Transform at turbojpeg.c:2871:15 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
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
#include <turbojpeg.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    tjhandle handle = tj3Init(TJINIT_TRANSFORM);
    if (!handle) return 0;

    tjtransform transform;
    memset(&transform, 0, sizeof(transform));

    size_t bufSize = tj3TransformBufSize(handle, &transform);
    if (bufSize == 0) {
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *dstBuf = (unsigned char *)tj3Alloc(bufSize);
    if (!dstBuf) {
        tj3Destroy(handle);
        return 0;
    }

    size_t dstSize = bufSize;
    int result = tj3Transform(handle, Data, Size, 1, &dstBuf, &dstSize, &transform);
    if (result != 0) {
        tj3Free(dstBuf);
        tj3Destroy(handle);
        return 0;
    }

    bufSize = tj3TransformBufSize(handle, &transform);
    if (bufSize == 0) {
        tj3Free(dstBuf);
        tj3Destroy(handle);
        return 0;
    }

    unsigned char *dstBuf2 = (unsigned char *)tj3Alloc(bufSize);
    if (!dstBuf2) {
        tj3Free(dstBuf);
        tj3Destroy(handle);
        return 0;
    }

    dstSize = bufSize;
    result = tj3Transform(handle, Data, Size, 1, &dstBuf2, &dstSize, &transform);
    if (result != 0) {
        tj3Free(dstBuf);
        tj3Free(dstBuf2);
        tj3Destroy(handle);
        return 0;
    }

    result = tj3Set(handle, TJPARAM_QUALITY, 85);
    if (result != 0) {
        tj3Free(dstBuf);
        tj3Free(dstBuf2);
        tj3Destroy(handle);
        return 0;
    }

    dstSize = bufSize;
    result = tj3Transform(handle, Data, Size, 1, &dstBuf, &dstSize, &transform);
    if (result != 0) {
        tj3Free(dstBuf);
        tj3Free(dstBuf2);
        tj3Destroy(handle);
        return 0;
    }

    tj3Free(dstBuf);
    tj3Free(dstBuf2);
    tj3Destroy(handle);
    return 0;
}