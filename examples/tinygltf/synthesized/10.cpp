// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::LoadBinaryFromMemory at tiny_gltf.cc:5109:16 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadASCIIFromString at tiny_gltf.cc:5053:16 in tiny_gltf.h
// tinygltf::TinyGLTF::WriteGltfSceneToStream at tiny_gltf.cc:6937:16 in tiny_gltf.h
// tinygltf::TinyGLTF::WriteGltfSceneToFile at tiny_gltf.cc:6994:16 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadBinaryFromFile at tiny_gltf.cc:5291:16 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadASCIIFromFile at tiny_gltf.cc:5066:16 in tiny_gltf.h
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
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    // Test LoadBinaryFromMemory
    loader.LoadBinaryFromMemory(&model, &err, &warn, Data, Size);

    // Test LoadASCIIFromString
    std::string asciiData(reinterpret_cast<const char*>(Data), Size);
    loader.LoadASCIIFromString(&model, &err, &warn, asciiData.c_str(), Size, "");

    // Test WriteGltfSceneToStream
    std::ostringstream oss;
    loader.WriteGltfSceneToStream(&model, oss, false, false);

    // Test WriteGltfSceneToFile
    loader.WriteGltfSceneToFile(&model, "./dummy_file", false, false, false, false);

    // Test LoadBinaryFromFile
    std::ofstream outFile("./dummy_file", std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(Data), Size);
    outFile.close();
    loader.LoadBinaryFromFile(&model, &err, &warn, "./dummy_file");

    // Test LoadASCIIFromFile
    loader.LoadASCIIFromFile(&model, &err, &warn, "./dummy_file");

    return 0;
}