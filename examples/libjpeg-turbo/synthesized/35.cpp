// This fuzz driver is generated for library libjpeg-turbo, aiming to fuzz the following functions:
// tj3Init at turbojpeg.c:542:20 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3Destroy at turbojpeg.c:584:16 in turbojpeg.h
// tj3DecompressHeader at turbojpeg.c:1819:15 in turbojpeg.h
// tj3GetScalingFactors at turbojpeg.c:1963:28 in turbojpeg.h
// tj3SetScalingFactor at turbojpeg.c:1985:15 in turbojpeg.h
// tj3SetCroppingRegion at turbojpeg.c:2010:15 in turbojpeg.h
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

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    // Create a dummy JPEG file
    FILE *file = fopen("./dummy_file", "wb");
    if (!file) {
        tj3Destroy(handle);
        return 0;
    }
    fwrite(Data, 1, Size, file);
    fclose(file);

    // Read the dummy JPEG file
    file = fopen("./dummy_file", "rb");
    if (!file) {
        tj3Destroy(handle);
        return 0;
    }
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    uint8_t *jpegBuf = (uint8_t *)malloc(fileSize);
    if (!jpegBuf) {
        fclose(file);
        tj3Destroy(handle);
        return 0;
    }
    fread(jpegBuf, 1, fileSize, file);
    fclose(file);

    // Decompress header
    tj3DecompressHeader(handle, jpegBuf, fileSize);

    // Set scaling factor
    int numScalingFactors;
    tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
    if (scalingFactors && numScalingFactors > 0) {
        tj3SetScalingFactor(handle, scalingFactors[0]);
    }

    // Set cropping region
    tjregion croppingRegion = {0, 0, 100, 100};
    tj3SetCroppingRegion(handle, croppingRegion);

    // Cleanup
    free(jpegBuf);
    tj3Destroy(handle);

    return 0;
}