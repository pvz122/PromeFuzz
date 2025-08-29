// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsInt at tiny_gltf.h:302:8 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::ArrayLen at tiny_gltf.h:358:10 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:342:16 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:351:16 in tiny_gltf.h
// tinygltf::Value::IsBool at tiny_gltf.h:300:8 in tiny_gltf.h
// tinygltf::Value::Type at tiny_gltf.h:298:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::GetNumberAsDouble at tiny_gltf.h:317:10 in tiny_gltf.h
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

extern "C" int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    tinygltf::Value value;

    // Initialize value with different types based on input data
    switch (Data[0] % 6) {
        case 0:
            value = tinygltf::Value(static_cast<int>(Data[1]));
            break;
        case 1:
            value = tinygltf::Value(static_cast<double>(Data[1]));
            break;
        case 2:
            value = tinygltf::Value(std::string(reinterpret_cast<const char*>(Data + 1), Size - 1));
            break;
        case 3:
            value = tinygltf::Value(std::vector<unsigned char>(Data + 1, Data + Size));
            break;
        case 4:
            value = tinygltf::Value(tinygltf::Value::Array());
            break;
        case 5:
            value = tinygltf::Value(tinygltf::Value::Object());
            break;
    }

    // Test IsInt
    value.IsInt();

    // Test Get
    if (value.IsArray() && value.ArrayLen() > 0) {
        value.Get(0);
    } else if (value.IsObject()) {
        value.Get("key");
    }

    // Test IsBool
    value.IsBool();

    // Test Type
    value.Type();

    // Test IsNumber
    value.IsNumber();

    // Test GetNumberAsDouble
    if (value.IsNumber()) {
        value.GetNumberAsDouble();
    }

    return 0;
}