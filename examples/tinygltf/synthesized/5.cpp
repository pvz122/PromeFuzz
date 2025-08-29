// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::LoadBinaryFromFile at tiny_gltf.cc:5291:16 in tiny_gltf.h
// tinygltf::TinyGLTF::GetMaxExternalFileSize at tiny_gltf.h:1565:10 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadBinaryFromMemory at tiny_gltf.cc:5109:16 in tiny_gltf.h
// tinygltf::TinyGLTF::WriteGltfSceneToFile at tiny_gltf.cc:6994:16 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadASCIIFromFile at tiny_gltf.cc:5066:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetMaxExternalFileSize at tiny_gltf.h:1561:8 in tiny_gltf.h
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
#include <fstream>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    static tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    // Write the input data to a dummy file
    std::ofstream outfile("./dummy_file", std::ios::binary);
    if (!outfile) return 0;
    outfile.write(reinterpret_cast<const char*>(Data), Size);
    outfile.close();

    // Test LoadBinaryFromFile
    loader.LoadBinaryFromFile(&model, &err, &warn, "./dummy_file");

    // Test GetMaxExternalFileSize
    size_t max_size = loader.GetMaxExternalFileSize();

    // Test LoadBinaryFromMemory
    loader.LoadBinaryFromMemory(&model, &err, &warn, Data, Size);

    // Test WriteGltfSceneToFile
    loader.WriteGltfSceneToFile(&model, "./dummy_file", false, false, false, false);

    // Test LoadASCIIFromFile
    loader.LoadASCIIFromFile(&model, &err, &warn, "./dummy_file");

    // Test SetMaxExternalFileSize
    loader.SetMaxExternalFileSize(max_size);

    return 0;
}