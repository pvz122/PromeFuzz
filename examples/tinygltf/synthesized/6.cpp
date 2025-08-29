// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::Type at tiny_gltf.h:298:8 in tiny_gltf.h
// tinygltf::Value::GetNumberAsInt at tiny_gltf.h:327:7 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::IsReal at tiny_gltf.h:306:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:414:1 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:415:1 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:416:1 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:417:1 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:418:1 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a Value object with binary data
    std::vector<unsigned char> binaryData(Data, Data + Size);
    tinygltf::Value value(std::move(binaryData));

    // Call the target API functions
    char type = value.Type();
    int numberAsInt = value.GetNumberAsInt();
    bool isBool = value.IsBool();
    bool isObject = value.IsObject();
    bool isReal = value.IsReal();

    // Attempt to get values from the Value object
    try {
        int intValue = value.Get<int>();
        std::string stringValue = value.Get<std::string>();
        std::vector<unsigned char> binaryValue = value.Get<std::vector<unsigned char>>();
        tinygltf::Value::Array arrayValue = value.Get<tinygltf::Value::Array>();
        tinygltf::Value::Object objectValue = value.Get<tinygltf::Value::Object>();
    } catch (...) {
        // Handle exceptions if any
    }

    return 0;
}