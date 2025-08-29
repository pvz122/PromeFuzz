// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3LoadImage16 at turbojpeg-mp.c:293:21 in turbojpeg.h
// tj3JPEGBufSize at turbojpeg.c:907:18 in turbojpeg.h
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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    tj3Set(handle, TJPARAM_QUALITY, 75);
    tj3Set(handle, TJPARAM_SUBSAMP, TJSAMP_420);
    tj3Set(handle, TJPARAM_OPTIMIZE, 1);
    tj3Set(handle, TJPARAM_ARITHMETIC, 0);
    tj3Set(handle, TJPARAM_PROGRESSIVE, 0);

    std::ofstream outFile("./dummy_file", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();

    int width, height, pixelFormat = TJPF_UNKNOWN;
    unsigned short *image = tj3LoadImage16(handle, "./dummy_file", &width, 1, &height, &pixelFormat);
    if (image) {
        size_t bufSize = tj3JPEGBufSize(width, height, TJSAMP_420);
        tj3Free(image);
    }

    tj3Destroy(handle);
    return 0;
}