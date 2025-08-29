// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::LoadBinaryFromFile at tiny_gltf.cc:5291:16 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadASCIIFromFile at tiny_gltf.cc:5066:16 in tiny_gltf.h
// tinygltf::Accessor::ByteStride at tiny_gltf.h:868:7 in tiny_gltf.h
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
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    static tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    // Write the input data to a dummy file
    std::ofstream outfile("./dummy_file", std::ios::binary);
    outfile.write(reinterpret_cast<const char*>(Data), Size);
    outfile.close();

    // Load binary glTF
    loader.LoadBinaryFromFile(&model, &err, &warn, "./dummy_file");

    // Load ASCII glTF
    loader.LoadASCIIFromFile(&model, &err, &warn, "./dummy_file");

    // Create a dummy BufferView and Accessor
    tinygltf::BufferView bufferView;
    tinygltf::Accessor accessor;

    // Compute byte stride for the BufferView
    accessor.ByteStride(bufferView);

    // Compute byte stride again for the BufferView
    accessor.ByteStride(bufferView);

    return 0;
}