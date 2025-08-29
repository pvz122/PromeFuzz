// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsBinary at tiny_gltf.h:310:8 in tiny_gltf.h
// tinygltf::Value::IsReal at tiny_gltf.h:306:8 in tiny_gltf.h
// tinygltf::Value::IsString at tiny_gltf.h:308:8 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:412:1 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a Value object with a boolean type
    tinygltf::Value value(static_cast<bool>(Data[0] % 2));

    // Test IsBinary
    (void)value.IsBinary();

    // Test IsReal
    (void)value.IsReal();

    // Test IsString
    (void)value.IsString();

    // Test IsObject
    (void)value.IsObject();

    // Test IsBool
    (void)value.IsBool();

    // Test Get for boolean
    if (value.IsBool()) {
        (void)value.Get<bool>();
    }

    return 0;
}