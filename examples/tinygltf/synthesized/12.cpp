// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::DecodeDataURI at tiny_gltf.cc:1732:6 in tiny_gltf.h
// tinygltf::URIDecode at tiny_gltf.cc:842:6 in tiny_gltf.h
// tinygltf::FileExists at tiny_gltf.cc:1265:6 in tiny_gltf.h
// tinygltf::TinyGLTF::SetURICallbacks at tiny_gltf.cc:1211:16 in tiny_gltf.h
// tinygltf::LoadImageData at tiny_gltf.cc:971:6 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImagesAsIs at tiny_gltf.h:1550:8 in tiny_gltf.h
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
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize necessary variables
    std::vector<unsigned char> out;
    std::string mime_type;
    std::string in_uri(reinterpret_cast<const char*>(Data), Size);
    std::string out_uri;
    tinygltf::Image image;
    std::string err;
    std::string warn;
    tinygltf::URICallbacks callbacks;
    tinygltf::TinyGLTF loader;

    // Fuzz DecodeDataURI
    tinygltf::DecodeDataURI(&out, mime_type, in_uri, Size, true);

    // Fuzz URIDecode
    tinygltf::URIDecode(in_uri, &out_uri, nullptr);

    // Fuzz FileExists
    tinygltf::FileExists("./dummy_file", nullptr);

    // Fuzz SetURICallbacks
    callbacks.decode = tinygltf::URIDecode;
    loader.SetURICallbacks(callbacks, &err);

    // Fuzz LoadImageData
    tinygltf::LoadImageData(&image, 0, &err, &warn, 100, 100, Data, Size, nullptr);

    // Fuzz SetImagesAsIs
    loader.SetImagesAsIs(true);

    return 0;
}