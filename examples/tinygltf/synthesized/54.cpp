// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsInt at tiny_gltf.h:302:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::GetNumberAsInt at tiny_gltf.h:327:7 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::ArrayLen at tiny_gltf.h:358:10 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:342:16 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:351:16 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a Value object with a boolean
    tinygltf::Value value(static_cast<bool>(Data[0] % 2));

    // Test IsInt
    bool isInt = value.IsInt();

    // Test GetNumberAsInt
    if (value.IsNumber()) {
        int numAsInt = value.GetNumberAsInt();
    }

    // Test Get for different types
    if (value.IsArray() && value.ArrayLen() > 0) {
        tinygltf::Value arrayElement = value.Get(0);
    }

    if (value.IsObject()) {
        tinygltf::Value objectElement = value.Get("key");
    }

    // Test IsBool
    bool isBool = value.IsBool();

    // Test IsNumber
    bool isNumber = value.IsNumber();

    return 0;
}