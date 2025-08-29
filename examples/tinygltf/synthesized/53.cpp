// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::GetImagesAsIs at tiny_gltf.h:1554:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImagesAsIs at tiny_gltf.h:1550:8 in tiny_gltf.h
// tinygltf::TinyGLTF::GetPreserveImageChannels at tiny_gltf.h:1545:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetSerializeDefaultValues at tiny_gltf.h:1518:8 in tiny_gltf.h
// tinygltf::TinyGLTF::GetSerializeDefaultValues at tiny_gltf.h:1522:8 in tiny_gltf.h
// tinygltf::TinyGLTF::WriteGltfSceneToFile at tiny_gltf.cc:6994:16 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;

    // Set up dummy file
    std::ofstream outfile("./dummy_file", std::ios::binary);
    outfile.write(reinterpret_cast<const char*>(Data), Size);
    outfile.close();

    // Test GetImagesAsIs and SetImagesAsIs
    bool imagesAsIs = loader.GetImagesAsIs();
    loader.SetImagesAsIs(!imagesAsIs);

    // Test GetPreserveImageChannels
    bool preserveChannels = loader.GetPreserveImageChannels();

    // Test SetSerializeDefaultValues and GetSerializeDefaultValues
    loader.SetSerializeDefaultValues(true);
    bool serializeDefaults = loader.GetSerializeDefaultValues();

    // Test WriteGltfSceneToFile
    bool writeResult = loader.WriteGltfSceneToFile(&model, "./dummy_file", true, true, true, false);

    return 0;
}