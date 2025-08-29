// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3EncodeYUVPlanes8 at turbojpeg.c:1512:15 in turbojpeg.h
// tjCompress2 at turbojpeg.c:1208:15 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3DecodeYUVPlanes8 at turbojpeg.c:2512:15 in turbojpeg.h
// tjInitTransform at turbojpeg.c:2752:20 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3CompressFromYUVPlanes8 at turbojpeg.c:1263:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 16) return 0;

    tjhandle handle = tj3Init(TJINIT_COMPRESS);
    if (!handle) return 0;

    int width = 16;
    int height = 16;
    int pitch = width * tjPixelSize[TJPF_RGB];
    int pixelFormat = TJPF_RGB;
    unsigned char *srcBuf = (unsigned char *)malloc(pitch * height);
    if (!srcBuf) {
        tj3Destroy(handle);
        return 0;
    }
    memcpy(srcBuf, Data, std::min(Size, (size_t)(pitch * height)));

    unsigned char *dstPlanes[3];
    int strides[3] = {0, 0, 0};
    dstPlanes[0] = (unsigned char *)malloc(width * height);
    dstPlanes[1] = (unsigned char *)malloc(width * height / 4);
    dstPlanes[2] = (unsigned char *)malloc(width * height / 4);
    if (!dstPlanes[0] || !dstPlanes[1] || !dstPlanes[2]) {
        free(srcBuf);
        tj3Destroy(handle);
        return 0;
    }

    tj3EncodeYUVPlanes8(handle, srcBuf, width, pitch, height, pixelFormat, dstPlanes, strides);

    unsigned char *jpegBuf = nullptr;
    unsigned long jpegSize = 0;
    tjCompress2(handle, srcBuf, width, pitch, height, pixelFormat, &jpegBuf, &jpegSize, TJSAMP_420, 75, 0);

    unsigned char *decodedBuf = (unsigned char *)malloc(pitch * height);
    if (!decodedBuf) {
        free(srcBuf);
        tj3Destroy(handle);
        return 0;
    }

    tj3DecodeYUVPlanes8(handle, (const unsigned char *const *)dstPlanes, strides, decodedBuf, width, pitch, height, pixelFormat);

    tjhandle transformHandle = tjInitTransform();
    if (transformHandle) {
        tj3Destroy(transformHandle);
    }

    tj3CompressFromYUVPlanes8(handle, (const unsigned char *const *)dstPlanes, width, strides, height, &jpegBuf, &jpegSize);

    free(srcBuf);
    free(dstPlanes[0]);
    free(dstPlanes[1]);
    free(dstPlanes[2]);
    free(decodedBuf);
    if (jpegBuf) tj3Free(jpegBuf);
    tj3Destroy(handle);

    return 0;
}