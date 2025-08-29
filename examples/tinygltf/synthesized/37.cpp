// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::SetImagesAsIs at tiny_gltf.h:1550:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImageWriter at tiny_gltf.cc:1105:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetPreserveImageChannels at tiny_gltf.h:1541:8 in tiny_gltf.h
// tinygltf::TinyGLTF::RemoveImageLoader at tiny_gltf.cc:958:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImageLoader at tiny_gltf.cc:948:16 in tiny_gltf.h
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
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tinygltf::TinyGLTF loader;
    bool onoff = Data[0] & 1;

    // Test SetImagesAsIs
    loader.SetImagesAsIs(onoff);

    // Test SetImageWriter
    auto dummyImageWriter = [](const std::string *basepath, const std::string *filename, const tinygltf::Image *image, bool embedImages, const tinygltf::FsCallbacks *, const tinygltf::URICallbacks *, std::string *, void *user_data) -> bool {
        return true;
    };
    loader.SetImageWriter(dummyImageWriter, nullptr);

    // Test SetPreserveImageChannels
    loader.SetPreserveImageChannels(onoff);

    // Test RemoveImageLoader
    loader.RemoveImageLoader();

    // Test SetImageLoader
    auto dummyImageLoader = [](tinygltf::Image *image, const int image_idx, std::string *err, std::string *warn, int req_width, int req_height, const unsigned char *bytes, int size, void *user_data) -> bool {
        return true;
    };
    loader.SetImageLoader(dummyImageLoader, nullptr);

    // Test LoadImageData
    tinygltf::Image image;
    std::string err, warn;
    int req_width = 0, req_height = 0;
    const unsigned char *bytes = Data;
    int size = Size;
    bool as_is = onoff;
    tinygltf::LoadImageData(&image, 0, &err, &warn, req_width, req_height, bytes, size, nullptr);

    return 0;
}