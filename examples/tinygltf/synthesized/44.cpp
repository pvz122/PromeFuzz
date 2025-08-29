// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::IsInt at tiny_gltf.h:302:8 in tiny_gltf.h
// tinygltf::Value::GetNumberAsInt at tiny_gltf.h:327:7 in tiny_gltf.h
// tinygltf::Value::Type at tiny_gltf.h:298:8 in tiny_gltf.h
// tinygltf::Value::IsNumber at tiny_gltf.h:304:8 in tiny_gltf.h
// tinygltf::Value::GetNumberAsDouble at tiny_gltf.h:317:10 in tiny_gltf.h
// tinygltf::Value::IsObject at tiny_gltf.h:314:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:351:16 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::Get at tiny_gltf.h:342:16 in tiny_gltf.h
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create a dummy Value object
    tinygltf::Value value;

    // Initialize the Value object based on the first byte of input
    switch (Data[0] % 6) {
        case 0:
            value = tinygltf::Value(static_cast<int>(Data[1]));
            break;
        case 1:
            value = tinygltf::Value(static_cast<double>(Data[1]));
            break;
        case 2:
            value = tinygltf::Value("dummy_string");
            break;
        case 3:
            value = tinygltf::Value(std::vector<unsigned char>(Data, Data + Size));
            break;
        case 4:
            value = tinygltf::Value(tinygltf::Value::Array());
            break;
        case 5:
            value = tinygltf::Value(tinygltf::Value::Object());
            break;
        default:
            break;
    }

    // Call the target API functions
    bool isInt = value.IsInt();
    if (isInt) {
        int intValue = value.GetNumberAsInt();
    }

    char type = value.Type();
    bool isNumber = value.IsNumber();
    if (isNumber) {
        double doubleValue = value.GetNumberAsDouble();
    }

    // Try to get values from the Value object
    if (value.IsObject()) {
        tinygltf::Value dummyValue = value.Get("dummy_key");
    } else if (value.IsArray()) {
        tinygltf::Value dummyValue = value.Get(0);
    }

    return 0;
}