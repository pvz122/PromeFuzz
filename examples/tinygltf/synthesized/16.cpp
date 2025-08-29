// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::IsInt at tiny_gltf.h:302:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::GetNumberAsDouble at tiny_gltf.h:317:10 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:412:1 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:413:1 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a tinygltf::Value object with a boolean value
    bool boolValue = Data[0] % 2 == 0;
    tinygltf::Value value(boolValue);

    // Test IsBool function
    bool isBool = value.IsBool();

    // Test IsNumber function
    bool isNumber = value.IsNumber();

    // Test IsInt function
    bool isInt = value.IsInt();

    // Test GetNumberAsDouble function
    if (value.IsNumber()) {
        double numberAsDouble = value.GetNumberAsDouble();
    }

    // Test Get function for boolean
    bool getBool = value.Get<bool>();

    // Test Get function for double
    if (value.IsNumber()) {
        double getDouble = value.Get<double>();
    }

    return 0;
}