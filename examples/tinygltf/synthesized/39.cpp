// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::SetImagesAsIs at tiny_gltf.h:1550:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetPreserveImageChannels at tiny_gltf.h:1541:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImageLoader at tiny_gltf.cc:948:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImageLoader at tiny_gltf.cc:948:16 in tiny_gltf.h
// tinygltf::TinyGLTF::RemoveImageLoader at tiny_gltf.cc:958:16 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImageWriter at tiny_gltf.cc:1105:16 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Image image;
    std::string err;
    std::string warn;

    // Randomly set the image-related options
    if (Size > 0) {
        loader.SetImagesAsIs(Data[0] & 1);
        loader.SetPreserveImageChannels(Data[0] & 2);
    }

    // Randomly set or remove the image loader
    if (Size > 1) {
        if (Data[1] & 1) {
            loader.SetImageLoader(nullptr, nullptr);
        } else {
            loader.SetImageLoader(tinygltf::LoadImageData, nullptr);
        }
    }

    // Randomly remove the image loader
    if (Size > 2 && Data[2] & 1) {
        loader.RemoveImageLoader();
    }

    // Randomly set the image writer
    if (Size > 3) {
        loader.SetImageWriter(nullptr, nullptr);
    }

    // Attempt to load image data with random input
    if (Size > 4) {
        tinygltf::LoadImageData(&image, 0, &err, &warn, 0, 0, Data, Size, nullptr);
    }

    return 0;
}