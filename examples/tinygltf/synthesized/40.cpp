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

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tinygltf::Value value(true);

    bool isBinary = value.IsBinary();
    bool isArray = value.IsArray();
    bool hasKey = value.Has("dummy_key");
    
    if (value.IsArray() && value.ArrayLen() > 0) {
        const tinygltf::Value &retrievedValue = value.Get(0);
    }

    size_t arrayLen = value.ArrayLen();
    size_t size = value.Size();

    return 0;
}