// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::SetParseStrictness at tiny_gltf.cc:944:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImagesAsIs at tiny_gltf.h:1550:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImageWriter at tiny_gltf.cc:1105:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetPreserveImageChannels at tiny_gltf.h:1541:8 in tiny_gltf.h
// tinygltf::TinyGLTF::WriteGltfSceneToFile at tiny_gltf.cc:6994:16 in tiny_gltf.h
// tinygltf::LoadImageData at tiny_gltf.cc:971:6 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;

    // Fuzz SetParseStrictness
    if (Size > 0) {
        loader.SetParseStrictness(static_cast<tinygltf::ParseStrictness>(Data[0] % 2));
    }

    // Fuzz SetImagesAsIs
    if (Size > 1) {
        loader.SetImagesAsIs(Data[1] % 2);
    }

    // Fuzz SetImageWriter
    if (Size > 2) {
        auto dummyImageWriter = [](const std::string *basepath, const std::string *filename, const tinygltf::Image *image, bool embedImages, const tinygltf::FsCallbacks *, const tinygltf::URICallbacks *, std::string *, void *user_data) -> bool {
            return true;
        };
        loader.SetImageWriter(dummyImageWriter, nullptr);
    }

    // Fuzz SetPreserveImageChannels
    if (Size > 3) {
        loader.SetPreserveImageChannels(Data[3] % 2);
    }

    // Fuzz WriteGltfSceneToFile
    if (Size > 7) {
        std::string filename = "./dummy_file";
        loader.WriteGltfSceneToFile(&model, filename, Data[4] % 2, Data[5] % 2, Data[6] % 2, Data[7] % 2);
    }

    // Fuzz LoadImageData
    if (Size > 8) {
        tinygltf::Image image;
        std::string err, warn;
        tinygltf::LoadImageData(&image, 0, &err, &warn, 0, 0, Data, Size, nullptr);
    }

    return 0;
}