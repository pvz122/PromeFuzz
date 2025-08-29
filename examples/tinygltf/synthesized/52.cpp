// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsInt at tiny_gltf.h:302:8 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:413:1 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::Type at tiny_gltf.h:298:8 in tiny_gltf.h
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
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a Value object with a double
    tinygltf::Value value(static_cast<double>(Data[0]));

    // Test IsInt
    bool isInt = value.IsInt();

    // Test IsArray
    bool isArray = value.IsArray();

    // Test Get (assuming the value is a number)
    if (value.IsNumber()) {
        double num = value.Get<double>();
    }

    // Test IsBool
    bool isBool = value.IsBool();

    // Test Type
    char type = value.Type();

    // Test IsNumber
    bool isNumber = value.IsNumber();

    return 0;
}