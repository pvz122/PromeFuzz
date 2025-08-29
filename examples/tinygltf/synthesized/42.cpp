// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsBinary at tiny_gltf.h:310:8 in tiny_gltf.h
// tinygltf::Value::IsReal at tiny_gltf.h:306:8 in tiny_gltf.h
// tinygltf::Value::IsString at tiny_gltf.h:308:8 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:415:1 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a Value object with a string type
    std::string input(reinterpret_cast<const char*>(Data), Size);
    tinygltf::Value value(input);

    // Test IsBinary
    bool isBinary = value.IsBinary();

    // Test IsReal
    bool isReal = value.IsReal();

    // Test IsString
    bool isString = value.IsString();

    // Test IsObject
    bool isObject = value.IsObject();

    // Test IsBool
    bool isBool = value.IsBool();

    // Test Get for string type
    if (isString) {
        std::string strValue = value.Get<std::string>();
    }

    return 0;
}