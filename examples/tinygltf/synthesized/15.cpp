// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::DecodeDataURI at tiny_gltf.cc:1732:6 in tiny_gltf.h
// tinygltf::URIDecode at tiny_gltf.cc:842:6 in tiny_gltf.h
// tinygltf::FileExists at tiny_gltf.cc:1265:6 in tiny_gltf.h
// tinygltf::ExpandFilePath at tiny_gltf.cc:1333:13 in tiny_gltf.h
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
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);

    // Test DecodeDataURI
    std::vector<unsigned char> out_data;
    std::string mime_type;
    tinygltf::DecodeDataURI(&out_data, mime_type, input, 0, false);

    // Test URIDecode
    std::string out_uri;
    tinygltf::URIDecode(input, &out_uri, nullptr);

    // Test FileExists
    tinygltf::FileExists(input, nullptr);

    // Test ExpandFilePath
    tinygltf::ExpandFilePath(input, nullptr);

    // Test WriteImageData
    tinygltf::Image image;
    std::string out_uri_image;
    tinygltf::FsCallbacks fs_cb;
    tinygltf::URICallbacks uri_cb;
    tinygltf::WriteImageData(nullptr, &input, &image, false, &fs_cb, &uri_cb, &out_uri_image, nullptr);

    // Test IsDataURI
    tinygltf::IsDataURI(input);

    return 0;
}