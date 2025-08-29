// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Parameter::Factor at tiny_gltf.h:495:10 in tiny_gltf.h
// tinygltf::Parameter::ColorFactor at tiny_gltf.h:500:14 in tiny_gltf.h
// tinygltf::Parameter::TextureScale at tiny_gltf.h:471:10 in tiny_gltf.h
// tinygltf::Parameter::TextureTexCoord at tiny_gltf.h:459:7 in tiny_gltf.h
// tinygltf::Parameter::TextureIndex at tiny_gltf.h:448:7 in tiny_gltf.h
// tinygltf::Parameter::TextureStrength at tiny_gltf.h:483:10 in tiny_gltf.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "tiny_gltf.h"

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    tinygltf::Parameter param;

    // Initialize the parameter with dummy data to avoid accessing uninitialized memory
    std::vector<double> number_array = {1.0, 1.0, 1.0, 1.0};
    param.number_array = number_array;

    // Call the target API functions
    double factor = param.Factor();
    tinygltf::ColorValue colorFactor = param.ColorFactor();
    double textureScale = param.TextureScale();
    int textureTexCoord = param.TextureTexCoord();
    int textureIndex = param.TextureIndex();
    double textureStrength = param.TextureStrength();

    // Prevent unused variable warnings
    (void)factor;
    (void)colorFactor;
    (void)textureScale;
    (void)textureTexCoord;
    (void)textureIndex;
    (void)textureStrength;

    return 0;
}