// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::Value::Size at tiny_gltf.h:383:10 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::Has at tiny_gltf.h:364:8 in tiny_gltf.h
// tinygltf::Value::ArrayLen at tiny_gltf.h:358:10 in tiny_gltf.h
// tinygltf::Value::IsBinary at tiny_gltf.h:310:8 in tiny_gltf.h
// tinygltf::Value::IsArray at tiny_gltf.h:312:8 in tiny_gltf.h
// tinygltf::Value::ArrayLen at tiny_gltf.h:358:10 in tiny_gltf.h
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
#include <string>

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    tinygltf::Value value;
    size_t idx = Data[0] % 256;
    std::string key(reinterpret_cast<const char*>(Data), Size);

    value.Size();
    value.IsArray();
    value.Has(key);
    value.ArrayLen();
    value.IsBinary();

    if (value.IsArray() && idx < value.ArrayLen()) {
        value.Get(idx);
    }

    return 0;
}