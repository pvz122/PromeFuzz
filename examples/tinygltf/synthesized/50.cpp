// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsInt at tiny_gltf.h:302:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::GetNumberAsInt at tiny_gltf.h:327:7 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:351:16 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::ArrayLen at tiny_gltf.h:358:10 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:342:16 in tiny_gltf.h
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
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a Value object with a string
    std::string str(reinterpret_cast<const char*>(Data), Size);
    tinygltf::Value value(std::move(str));

    // Test IsInt
    bool isInt = value.IsInt();

    // Test GetNumberAsInt
    if (value.IsNumber()) {
        int numAsInt = value.GetNumberAsInt();
    }

    // Test Get
    if (value.IsObject()) {
        tinygltf::Value objValue = value.Get("key");
    } else if (value.IsArray() && value.ArrayLen() > 0) {
        tinygltf::Value arrValue = value.Get(0);
    }

    // Test Type
    char type = value.Type();

    // Test IsNumber
    bool isNumber = value.IsNumber();

    // Test GetNumberAsDouble
    if (value.IsNumber()) {
        double numAsDouble = value.GetNumberAsDouble();
    }

    return 0;
}