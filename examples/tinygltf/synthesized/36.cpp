// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsBinary at tiny_gltf.h:310:8 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::Has at tiny_gltf.h:364:8 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::ArrayLen at tiny_gltf.h:358:10 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:342:16 in tiny_gltf.h
// tinygltf::Value::ArrayLen at tiny_gltf.h:358:10 in tiny_gltf.h
// tinygltf::Value::Size at tiny_gltf.h:383:10 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy string from the input data
    std::string dummyString(reinterpret_cast<const char*>(Data), Size);

    // Initialize a tinygltf::Value object with the dummy string
    tinygltf::Value value(dummyString.c_str());

    // Fuzz the IsBinary function
    (void)value.IsBinary();

    // Fuzz the IsArray function
    (void)value.IsArray();

    // Fuzz the Has function
    (void)value.Has("dummy_key");

    // Fuzz the Get function
    if (value.IsArray() && value.ArrayLen() > 0) {
        (void)value.Get(0);
    }

    // Fuzz the ArrayLen function
    (void)value.ArrayLen();

    // Fuzz the Size function
    (void)value.Size();

    return 0;
}