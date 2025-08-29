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

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tjhandle handle = tj3Init(TJINIT_DECOMPRESS);
    if (!handle) return 0;

    // Use a dummy file for fuzzing
    const char *dummy_file = "./dummy_file";
    FILE *fp = fopen(dummy_file, "wb");
    if (!fp) {
        tj3Destroy(handle);
        return 0;
    }
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    // Read the dummy file back into a buffer
    fp = fopen(dummy_file, "rb");
    if (!fp) {
        tj3Destroy(handle);
        return 0;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    uint8_t *jpegBuf = (uint8_t *)malloc(file_size);
    if (!jpegBuf) {
        fclose(fp);
        tj3Destroy(handle);
        return 0;
    }
    fread(jpegBuf, 1, file_size, fp);
    fclose(fp);

    // Decompress header
    if (tj3DecompressHeader(handle, jpegBuf, file_size) == 0) {
        // Get scaling factors
        int numScalingFactors;
        tjscalingfactor *scalingFactors = tj3GetScalingFactors(&numScalingFactors);
        if (scalingFactors && numScalingFactors > 0) {
            // Set scaling factor
            tj3SetScalingFactor(handle, scalingFactors[0]);

            // Set cropping region
            tjregion croppingRegion;
            croppingRegion.x = 0;
            croppingRegion.y = 0;
            croppingRegion.w = 100;
            croppingRegion.h = 100;
            tj3SetCroppingRegion(handle, croppingRegion);
        }
    }

    free(jpegBuf);
    tj3Destroy(handle);
    return 0;
}