// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsVEC3cross at cmsmtrx.c:50:16 in lcms2_plugin.h
// _cmsMAT3solve at cmsmtrx.c:156:20 in lcms2_plugin.h
// _cmsVEC3minus at cmsmtrx.c:42:16 in lcms2_plugin.h
// _cmsMAT3eval at cmsmtrx.c:169:16 in lcms2_plugin.h
// _cmsVEC3distance at cmsmtrx.c:72:28 in lcms2_plugin.h
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

extern "C" int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsVEC3) * 2 + sizeof(cmsMAT3)) return 0;

    cmsVEC3 vec1, vec2, result;
    cmsMAT3 mat;

    // Initialize vectors and matrix with fuzzed data
    memcpy(&vec1, Data, sizeof(cmsVEC3));
    memcpy(&vec2, Data + sizeof(cmsVEC3), sizeof(cmsVEC3));
    memcpy(&mat, Data + sizeof(cmsVEC3) * 2, sizeof(cmsMAT3));

    // Test _cmsVEC3cross
    _cmsVEC3cross(&result, &vec1, &vec2);

    // Test _cmsMAT3solve
    _cmsMAT3solve(&result, &mat, &vec1);

    // Test _cmsVEC3minus
    _cmsVEC3minus(&result, &vec1, &vec2);

    // Test _cmsMAT3eval
    _cmsMAT3eval(&result, &mat, &vec1);

    // Test _cmsVEC3distance
    _cmsVEC3distance(&vec1, &vec2);

    return 0;
}