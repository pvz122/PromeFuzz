// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3Get at turbojpeg.c:811:15 in turbojpeg.h
// tj3Alloc at turbojpeg.c:881:17 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Compress16 at turbojpeg-mp.c:71:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    int param = *reinterpret_cast<const int*>(Data);
    int value = tj3Get(handle, param);

    void *buffer = tj3Alloc(Size);
    if (!buffer) {
        tj3Destroy(handle);
        return 0;
    }

    memcpy(buffer, Data, Size);

    tj3Set(handle, TJPARAM_QUALITY, 75);
    tj3Set(handle, TJPARAM_SUBSAMP, TJSAMP_420);
    tj3Set(handle, TJPARAM_FASTDCT, 1);

    unsigned char *jpegBuf = nullptr;
    size_t jpegSize = 0;
    int width = 64;
    int height = 64;
    int pitch = width * 3;
    int pixelFormat = TJPF_RGB;

    tj3Compress16(handle, reinterpret_cast<const unsigned short*>(buffer), width, pitch, height, pixelFormat, &jpegBuf, &jpegSize);

    tj3Free(buffer);
    tj3Free(jpegBuf);
    tj3Destroy(handle);

    return 0;
}