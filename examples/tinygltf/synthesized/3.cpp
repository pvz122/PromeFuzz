// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::GetNumComponentsInType at tiny_gltf.h:228:23 in tiny_gltf.h
// tinygltf::LoadImageData at tiny_gltf.cc:971:6 in tiny_gltf.h
// tinygltf::Accessor::ByteStride at tiny_gltf.h:868:7 in tiny_gltf.h
// tinygltf::GetComponentSizeInBytes at tiny_gltf.h:205:23 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadASCIIFromFile at tiny_gltf.cc:5066:16 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadASCIIFromString at tiny_gltf.cc:5053:16 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    // Fuzz GetNumComponentsInType
    if (Size >= sizeof(uint32_t)) {
        uint32_t ty = *reinterpret_cast<const uint32_t*>(Data);
        tinygltf::GetNumComponentsInType(ty);
    }

    // Fuzz LoadImageData
    if (Size > 0) {
        tinygltf::Image image;
        std::string err, warn;
        int image_idx = 0;
        int req_width = 0, req_height = 0;
        tinygltf::LoadImageData(&image, image_idx, &err, &warn, req_width, req_height, Data, Size, nullptr);
    }

    // Fuzz Accessor::ByteStride
    if (Size >= sizeof(tinygltf::BufferView)) {
        tinygltf::Accessor accessor;
        tinygltf::BufferView bufferView;
        accessor.ByteStride(bufferView);
    }

    // Fuzz GetComponentSizeInBytes
    if (Size >= sizeof(uint32_t)) {
        uint32_t componentType = *reinterpret_cast<const uint32_t*>(Data);
        tinygltf::GetComponentSizeInBytes(componentType);
    }

    // Fuzz TinyGLTF::LoadASCIIFromFile
    if (Size > 0) {
        tinygltf::TinyGLTF loader;
        tinygltf::Model model;
        std::string err, warn;
        FILE *file = fopen("./dummy_file", "wb");
        if (file) {
            fwrite(Data, 1, Size, file);
            fclose(file);
            loader.LoadASCIIFromFile(&model, &err, &warn, "./dummy_file");
        }
    }

    // Fuzz TinyGLTF::LoadASCIIFromString
    if (Size > 0) {
        tinygltf::TinyGLTF loader;
        tinygltf::Model model;
        std::string err, warn;
        std::string base_dir = "./";
        loader.LoadASCIIFromString(&model, &err, &warn, reinterpret_cast<const char*>(Data), Size, base_dir);
    }

    return 0;
}