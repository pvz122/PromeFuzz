// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::DecodeDataURI at tiny_gltf.cc:1732:6 in tiny_gltf.h
// tinygltf::URIDecode at tiny_gltf.cc:842:6 in tiny_gltf.h
// tinygltf::FileExists at tiny_gltf.cc:1265:6 in tiny_gltf.h
// tinygltf::TinyGLTF::SetURICallbacks at tiny_gltf.cc:1211:16 in tiny_gltf.h
// tinygltf::WriteImageData at tiny_gltf.cc:1120:6 in tiny_gltf.h
// tinygltf::IsDataURI at tiny_gltf.cc:1693:6 in tiny_gltf.h
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
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Test DecodeDataURI
    std::vector<unsigned char> out;
    std::string mime_type;
    tinygltf::DecodeDataURI(&out, mime_type, input, 0, false);

    // Test URIDecode
    std::string out_uri;
    tinygltf::URIDecode(input, &out_uri, nullptr);

    // Test FileExists
    tinygltf::FileExists(input, nullptr);

    // Test SetURICallbacks
    tinygltf::TinyGLTF loader;
    tinygltf::URICallbacks uri_callbacks = {nullptr, [](const std::string &in_uri, std::string *out_uri, void *user_data) { return true; }, nullptr};
    std::string err;
    loader.SetURICallbacks(uri_callbacks, &err);

    // Test WriteImageData - FIX: Use valid filename with extension
    tinygltf::Image image;
    image.image = std::vector<unsigned char>(Data, Data + Size);
    std::string out_uri_write;
    std::string dummy_filename = "dummy.png";  // Ensure valid filename pointer with extension
    tinygltf::WriteImageData(nullptr, &dummy_filename, &image, false, nullptr, nullptr, &out_uri_write, nullptr);

    // Test IsDataURI
    tinygltf::IsDataURI(input);

    return 0;
}