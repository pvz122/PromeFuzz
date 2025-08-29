// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsMAT3inverse at cmsmtrx.c:129:20 in lcms2_plugin.h
// _cmsMAT3per at cmsmtrx.c:114:16 in lcms2_plugin.h
// _cmsMAT3isIdentity at cmsmtrx.c:98:19 in lcms2_plugin.h
// _cmsMAT3identity at cmsmtrx.c:84:16 in lcms2_plugin.h
// _cmsMAT3solve at cmsmtrx.c:156:20 in lcms2_plugin.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "lcms2_plugin.h"
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsMAT3) * 2 + sizeof(cmsVEC3) * 2) return 0;

    cmsMAT3 mat1, mat2, mat3;
    cmsVEC3 vec1, vec2;

    // Initialize matrices and vectors with fuzzed data
    memcpy(&mat1, Data, sizeof(cmsMAT3));
    memcpy(&mat2, Data + sizeof(cmsMAT3), sizeof(cmsMAT3));
    memcpy(&vec1, Data + sizeof(cmsMAT3) * 2, sizeof(cmsVEC3));
    memcpy(&vec2, Data + sizeof(cmsMAT3) * 2 + sizeof(cmsVEC3), sizeof(cmsVEC3));

    // Test _cmsMAT3inverse
    cmsMAT3 inverseMat;
    _cmsMAT3inverse(&mat1, &inverseMat);

    // Test _cmsMAT3per
    _cmsMAT3per(&mat3, &mat1, &mat2);

    // Test _cmsMAT3isIdentity
    _cmsMAT3isIdentity(&mat1);

    // Test _cmsMAT3identity
    _cmsMAT3identity(&mat1);

    // Test _cmsMAT3solve
    _cmsMAT3solve(&vec1, &mat1, &vec2);

    return 0;
}