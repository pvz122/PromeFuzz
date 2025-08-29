// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::FileExists at tiny_gltf.cc:1265:6 in tiny_gltf.h
// tinygltf::TinyGLTF::LoadBinaryFromFile at tiny_gltf.cc:5291:16 in tiny_gltf.h
// tinygltf::GetFileSizeInBytes at tiny_gltf.cc:1396:6 in tiny_gltf.h
// tinygltf::WriteWholeFile at tiny_gltf.cc:1590:6 in tiny_gltf.h
// tinygltf::TinyGLTF::SetFsCallbacks at tiny_gltf.cc:1225:16 in tiny_gltf.h
// tinygltf::ReadWholeFile at tiny_gltf.cc:1492:6 in tiny_gltf.h
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
#include <vector>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    std::string filename = "./dummy_file";
    FILE *fp = fopen(filename.c_str(), "wb");
    if (!fp) return 0;
    fwrite(Data, 1, Size, fp);
    fclose(fp);

    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    // Fuzz FileExists
    bool fileExists = tinygltf::FileExists(filename, nullptr);

    // Fuzz LoadBinaryFromFile
    bool loadBinary = loader.LoadBinaryFromFile(&model, &err, &warn, filename);

    // Fuzz GetFileSizeInBytes
    size_t fileSize;
    bool getFileSize = tinygltf::GetFileSizeInBytes(&fileSize, &err, filename, nullptr);

    // Fuzz WriteWholeFile
    std::vector<unsigned char> contents(Data, Data + Size);
    bool writeWholeFile = tinygltf::WriteWholeFile(&err, filename, contents, nullptr);

    // Fuzz SetFsCallbacks
    tinygltf::FsCallbacks callbacks = {
        [](const std::string &, void *) { return true; },
        [](const std::string &, void *) { return ""; },
        [](std::vector<unsigned char> *, std::string *, const std::string &, void *) { return true; },
        [](std::string *, const std::string &, const std::vector<unsigned char> &, void *) { return true; },
        [](size_t *, std::string *, const std::string &, void *) { return true; },
        nullptr
    };
    bool setFsCallbacks = loader.SetFsCallbacks(callbacks, &err);

    // Fuzz ReadWholeFile
    std::vector<unsigned char> out;
    bool readWholeFile = tinygltf::ReadWholeFile(&out, &err, filename, nullptr);

    return 0;
}