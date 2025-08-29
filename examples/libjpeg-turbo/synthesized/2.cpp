// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3DecompressHeader at turbojpeg.c:1819:15 in turbojpeg.h
// tj3Get at turbojpeg.c:811:15 in turbojpeg.h
// tj3Get at turbojpeg.c:811:15 in turbojpeg.h
// tj3Get at turbojpeg.c:811:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
// tj3Set at turbojpeg.c:675:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) {
        return 0;
    }

    if (tj3DecompressHeader(handle, Data, Size) == 0) {
        tj3Get(handle, TJPARAM_QUALITY);
        tj3Get(handle, TJPARAM_SUBSAMP);
        tj3Get(handle, TJPARAM_JPEGWIDTH);
    }

    tj3Set(handle, TJPARAM_QUALITY, 75);
    tj3Set(handle, TJPARAM_SUBSAMP, TJSAMP_420);

    tj3Destroy(handle);
    return 0;
}