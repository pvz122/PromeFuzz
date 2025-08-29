// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3YUVPlaneHeight at turbojpeg.c:1095:15 in turbojpeg.h
// tjBufSizeYUV at turbojpeg.c:1011:25 in turbojpeg.h
// tj3YUVPlaneWidth at turbojpeg.c:1061:15 in turbojpeg.h
// tj3YUVPlaneSize at turbojpeg.c:1024:18 in turbojpeg.h
// tjPlaneSizeYUV at turbojpeg.c:1052:25 in turbojpeg.h
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
#include <climits>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    int componentID = Data[0] % 3;
    int width = (Data[1] << 8) | Data[2];
    int height = (Data[3] << 8) | Data[4];
    int stride = (Data[5] << 8) | Data[6];
    int subsamp = Data[7] % 6;

    tj3YUVPlaneHeight(componentID, height, subsamp);
    tjBufSizeYUV(width, height, subsamp);
    tj3YUVPlaneWidth(componentID, width, subsamp);
    tj3YUVPlaneSize(componentID, width, stride, height, subsamp);
    tjPlaneSizeYUV(componentID, width, stride, height, subsamp);

    return 0;
}