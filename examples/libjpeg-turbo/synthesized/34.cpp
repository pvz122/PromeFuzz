// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjCompress2 at turbojpeg.c:1208:15 in turbojpeg.h
// tjFree at turbojpeg.c:900:16 in turbojpeg.h
// tjDecompress at turbojpeg.c:2112:15 in turbojpeg.h
// tjDecompressToYUVPlanes at turbojpeg.c:2292:15 in turbojpeg.h
// tjDecompress2 at turbojpeg.c:2063:15 in turbojpeg.h
// tj3GetICCProfile at turbojpeg.c:1930:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    // Randomly select a function to fuzz
    int choice = Data[0] % 5;
    Data++;
    Size--;

    switch (choice) {
        case 0: {
            // Fuzz tjCompress2
            int width = 64;
            int height = 64;
            int pitch = width * 3;
            int pixelFormat = TJPF_RGB;
            unsigned char *srcBuf = (unsigned char *)malloc(width * height * 3);
            if (!srcBuf) break;
            memcpy(srcBuf, Data, std::min(Size, (size_t)(width * height * 3)));

            unsigned char *jpegBuf = nullptr;
            unsigned long jpegSize = 0;
            int jpegSubsamp = TJSAMP_420;
            int jpegQual = 85;
            int flags = 0;

            tjCompress2(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize, jpegSubsamp, jpegQual, flags);

            if (jpegBuf) tjFree(jpegBuf);
            free(srcBuf);
            break;
        }
        case 1: {
            // Fuzz tjDecompress
            int width = 64;
            int height = 64;
            int pitch = width * 3;
            int pixelSize = 3;
            unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);
            if (!dstBuf) break;

            tjDecompress(handle, (unsigned char *)Data, Size, dstBuf, width, pitch, height, pixelSize, 0);

            free(dstBuf);
            break;
        }
        case 2: {
            // Fuzz tjDecompressToYUVPlanes
            int width = 64;
            int height = 64;
            int strides[3] = {width, width / 2, width / 2};
            unsigned char *dstPlanes[3];
            dstPlanes[0] = (unsigned char *)malloc(width * height);
            dstPlanes[1] = (unsigned char *)malloc(width * height / 4);
            dstPlanes[2] = (unsigned char *)malloc(width * height / 4);
            if (!dstPlanes[0] || !dstPlanes[1] || !dstPlanes[2]) break;

            tjDecompressToYUVPlanes(handle, (unsigned char *)Data, Size, dstPlanes, width, strides, height, 0);

            free(dstPlanes[0]);
            free(dstPlanes[1]);
            free(dstPlanes[2]);
            break;
        }
        case 3: {
            // Fuzz tjDecompress2
            int width = 64;
            int height = 64;
            int pitch = width * 3;
            int pixelFormat = TJPF_RGB;
            unsigned char *dstBuf = (unsigned char *)malloc(width * height * 3);
            if (!dstBuf) break;

            tjDecompress2(handle, (unsigned char *)Data, Size, dstBuf, width, pitch, height, pixelFormat, 0);

            free(dstBuf);
            break;
        }
        case 4: {
            // Fuzz tj3GetICCProfile
            unsigned char *iccBuf = nullptr;
            size_t iccSize = 0;
            tj3GetICCProfile(handle, &iccBuf, &iccSize);

            if (iccBuf) tj3Free(iccBuf);
            break;
        }
    }

    tjDestroy(handle);
    return 0;
}