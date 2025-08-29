// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::SetParseStrictness at tiny_gltf.cc:944:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImageLoader at tiny_gltf.cc:948:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImageWriter at tiny_gltf.cc:1105:16 in tiny_gltf.h
// tinygltf::TinyGLTF::RemoveImageLoader at tiny_gltf.cc:958:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetPreserveImageChannels at tiny_gltf.h:1541:8 in tiny_gltf.h
// tinygltf::WriteImageData at tiny_gltf.cc:1120:6 in tiny_gltf.h
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_25(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tinygltf::TinyGLTF loader;
    tinygltf::Image image;
    tinygltf::FsCallbacks fs_callbacks;
    tinygltf::URICallbacks uri_callbacks;
    std::string out_uri;

    // Set ParseStrictness
    loader.SetParseStrictness(static_cast<tinygltf::ParseStrictness>(Data[0] % 2));

    // Set ImageLoader
    loader.SetImageLoader(nullptr, nullptr);

    // Set ImageWriter
    loader.SetImageWriter(nullptr, nullptr);

    // Remove ImageLoader
    loader.RemoveImageLoader();

    // Set PreserveImageChannels
    loader.SetPreserveImageChannels(Data[0] % 2 == 0);

    // WriteImageData
    std::string basepath = "./dummy_file";
    std::string filename = "dummy_file";
    bool embedImages = Data[0] % 2 == 0;
    tinygltf::WriteImageData(&basepath, &filename, &image, embedImages, &fs_callbacks, &uri_callbacks, &out_uri, nullptr);

    return 0;
}