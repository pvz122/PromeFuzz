// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tjInitCompress at turbojpeg.c:1161:20 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjSaveImage at turbojpeg.c:3129:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tj3SaveImage16 at turbojpeg-mp.c:442:15 in turbojpeg.h
// tjDestroy at turbojpeg.c:605:15 in turbojpeg.h
// tjDecompress at turbojpeg.c:2112:15 in turbojpeg.h
// tj3LoadImage16 at turbojpeg-mp.c:293:21 in turbojpeg.h
// tj3Free at turbojpeg.c:894:16 in turbojpeg.h
// tj3Decompress16 at turbojpeg-mp.c:148:15 in turbojpeg.h
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
#include "turbojpeg.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tjInitCompress();
    if (!handle) return 0;

    const char *filename = "./dummy_file";
    FILE *file = fopen(filename, "wb");
    if (!file) {
        tjDestroy(handle);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    int width = 16;
    int height = 16;
    int pitch = width * 3;
    int pixelFormat = TJPF_RGB;
    int flags = 0;

    unsigned char *buffer = (unsigned char *)malloc(pitch * height);
    if (!buffer) {
        tjDestroy(handle);
        return 0;
    }

    tjSaveImage(filename, buffer, width, pitch, height, pixelFormat, flags);

    unsigned short *buffer16 = (unsigned short *)malloc(pitch * height * sizeof(unsigned short));
    if (!buffer16) {
        free(buffer);
        tjDestroy(handle);
        return 0;
    }

    tj3SaveImage16(handle, filename, buffer16, width, pitch, height, pixelFormat);

    unsigned char *jpegBuf = (unsigned char *)malloc(Size);
    if (!jpegBuf) {
        free(buffer16);
        free(buffer);
        tjDestroy(handle);
        return 0;
    }
    memcpy(jpegBuf, Data, Size);

    tjDecompress(handle, jpegBuf, Size, buffer, width, pitch, height, 3, flags);

    int align = 1;
    int loadedWidth, loadedHeight;
    int loadedPixelFormat = TJPF_UNKNOWN;
    unsigned short *loadedImage = tj3LoadImage16(handle, filename, &loadedWidth, align, &loadedHeight, &loadedPixelFormat);
    if (loadedImage) {
        tj3Free(loadedImage);
    }

    tj3Decompress16(handle, jpegBuf, Size, buffer16, pitch, pixelFormat);

    free(jpegBuf);
    free(buffer16);
    free(buffer);
    tjDestroy(handle);

    return 0;
}