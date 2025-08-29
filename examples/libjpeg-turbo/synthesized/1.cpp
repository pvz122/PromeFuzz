// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3JPEGBufSize at turbojpeg.c:907:18 in turbojpeg.h
// tj3Get at turbojpeg.c:811:15 in turbojpeg.h
// tj3Alloc at turbojpeg.c:881:17 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
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
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    int width = (Data[0] << 8) | Data[1];
    int height = (Data[2] << 8) | Data[3];
    int param = Data[4] % 10;
    int value = Data[5] % 256;

    tj3Set(handle, TJPARAM_QUALITY, 85);
    tj3Set(handle, TJPARAM_SUBSAMP, TJSAMP_420);
    tj3Set(handle, TJPARAM_FASTUPSAMPLE, 1);
    tj3Set(handle, TJPARAM_FASTDCT, 1);
    tj3Set(handle, TJPARAM_OPTIMIZE, 1);

    size_t bufSize = tj3JPEGBufSize(width, height, TJSAMP_420);
    int getValue = tj3Get(handle, TJPARAM_QUALITY);

    void *buffer = tj3Alloc(bufSize);
    if (buffer) {
        tj3Set(handle, TJPARAM_NOREALLOC, 1);
        tj3Set(handle, TJPARAM_RESTARTROWS, 0);
        tj3Set(handle, TJPARAM_RESTARTBLOCKS, 0);
        tj3Free(buffer);
    }

    tj3Free(nullptr);
    tj3Destroy(handle);

    return 0;
}