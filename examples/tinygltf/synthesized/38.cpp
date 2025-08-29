// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::LoadASCIIFromString at tiny_gltf.cc:5053:16 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadASCIIFromFile at tiny_gltf.cc:5066:16 in tiny_gltf.h
// tinygltf::GetComponentSizeInBytes at tiny_gltf.h:205:23 in tiny_gltf.h
// tinygltf::GetNumComponentsInType at tiny_gltf.h:228:23 in tiny_gltf.h
// tinygltf::Accessor::ByteStride at tiny_gltf.h:868:7 in tiny_gltf.h
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
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    // Fuzz LoadASCIIFromString
    loader.LoadASCIIFromString(&model, &err, &warn, reinterpret_cast<const char *>(Data), Size, "./dummy_file");

    // Fuzz LoadASCIIFromFile
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
    loader.LoadASCIIFromFile(&model, &err, &warn, "./dummy_file");

    // Fuzz GetComponentSizeInBytes
    tinygltf::GetComponentSizeInBytes(static_cast<uint32_t>(Size));

    // Fuzz GetNumComponentsInType
    tinygltf::GetNumComponentsInType(static_cast<uint32_t>(Size));

    // Fuzz ByteStride
    tinygltf::BufferView bufferView;
    tinygltf::Accessor accessor;
    accessor.ByteStride(bufferView);

    return 0;
}