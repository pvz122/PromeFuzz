// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::Has at tiny_gltf.h:364:8 in tiny_gltf.h
// tinygltf::Value::Keys at tiny_gltf.h:371:28 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:351:16 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a Value object with a dummy type
    tinygltf::Value value(static_cast<double>(Data[0]));

    // Call the target functions
    bool isArray = value.IsArray();
    bool isBool = value.IsBool();
    bool isObject = value.IsObject();
    
    // Only call Has, Keys, and Get if the value is an object
    if (isObject) {
        bool hasKey = value.Has("dummy_key");
        std::vector<std::string> keys = value.Keys();
        const tinygltf::Value& retrievedValue = value.Get("dummy_key");
    }

    return 0;
}