// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::IsReal at tiny_gltf.h:306:8 in tiny_gltf.h
// tinygltf::Value::IsString at tiny_gltf.h:308:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:412:1 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:413:1 in tiny_gltf.h
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
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a Value object with a string
    std::string input(reinterpret_cast<const char*>(Data), Size);
    tinygltf::Value value(std::move(input));

    // Call the target API functions
    bool isArray = value.IsArray();
    bool isBool = value.IsBool();
    bool isObject = value.IsObject();
    bool isReal = value.IsReal();
    bool isString = value.IsString();

    // Call the Get function with different types
    try {
        bool boolValue = value.Get<bool>();
        double realValue = value.Get<double>();
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