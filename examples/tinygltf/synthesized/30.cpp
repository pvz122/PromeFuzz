// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::GetSerializeDefaultValues at tiny_gltf.h:1522:8 in tiny_gltf.h
// tinygltf::TinyGLTF::GetPreserveImageChannels at tiny_gltf.h:1545:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImagesAsIs at tiny_gltf.h:1550:8 in tiny_gltf.h
// tinygltf::TinyGLTF::GetImagesAsIs at tiny_gltf.h:1554:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetPreserveImageChannels at tiny_gltf.h:1541:8 in tiny_gltf.h
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
#include <string>

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;

    // Test GetSerializeDefaultValues
    bool serializeDefaultValues = loader.GetSerializeDefaultValues();

    // Test GetPreserveImageChannels
    bool preserveImageChannels = loader.GetPreserveImageChannels();

    // Test SetImagesAsIs and GetImagesAsIs
    bool imagesAsIs = Size % 2 == 0;
    loader.SetImagesAsIs(imagesAsIs);
    bool getImagesAsIs = loader.GetImagesAsIs();

    // Test SetPreserveImageChannels
    bool preserveChannels = Size % 3 == 0;
    loader.SetPreserveImageChannels(preserveChannels);

    // Test WriteGltfSceneToFile
    std::string filename = "./dummy_file";
    std::ofstream outFile(filename, std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(Data), Size);
        outFile.close();
    }

    bool embedImages = Size % 4 == 0;
    bool embedBuffers = Size % 5 == 0;
    bool prettyPrint = Size % 6 == 0;
    bool writeBinary = Size % 7 == 0;
    loader.WriteGltfSceneToFile(&model, filename, embedImages, embedBuffers, prettyPrint, writeBinary);

    return 0;
}