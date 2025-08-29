// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::WriteGltfSceneToStream at tiny_gltf.cc:6937:16 in tiny_gltf.h
// tinygltf::TinyGLTF::GetSerializeDefaultValues at tiny_gltf.h:1522:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetStoreOriginalJSONForExtrasAndExtensions at tiny_gltf.h:1529:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetSerializeDefaultValues at tiny_gltf.h:1518:8 in tiny_gltf.h
// tinygltf::TinyGLTF::GetStoreOriginalJSONForExtrasAndExtensions at tiny_gltf.h:1533:8 in tiny_gltf.h
// tinygltf::TinyGLTF::WriteGltfSceneToFile at tiny_gltf.cc:6994:16 in tiny_gltf.h
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
#include <fstream>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;

    // Set up the model with some default values
    model.asset.version = "2.0";
    model.asset.generator = "FuzzTest";

    // Create a buffer and add it to the model
    tinygltf::Buffer buffer;
    buffer.data.assign(Data, Data + Size);
    model.buffers.push_back(buffer);

    // Create a buffer view and add it to the model
    tinygltf::BufferView bufferView;
    bufferView.buffer = 0;
    bufferView.byteOffset = 0;
    bufferView.byteLength = Size;
    model.bufferViews.push_back(bufferView);

    // Create an accessor and add it to the model
    tinygltf::Accessor accessor;
    accessor.bufferView = 0;
    accessor.byteOffset = 0;
    accessor.componentType = TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE;
    accessor.count = Size;
    accessor.type = TINYGLTF_TYPE_SCALAR;
    model.accessors.push_back(accessor);

    // Test WriteGltfSceneToStream
    std::ostringstream oss;
    loader.WriteGltfSceneToStream(&model, oss, true, false);

    // Test GetSerializeDefaultValues
    bool serializeDefaults = loader.GetSerializeDefaultValues();

    // Test SetStoreOriginalJSONForExtrasAndExtensions
    loader.SetStoreOriginalJSONForExtrasAndExtensions(true);

    // Test SetSerializeDefaultValues
    loader.SetSerializeDefaultValues(true);

    // Test GetStoreOriginalJSONForExtrasAndExtensions
    bool storeOriginalJSON = loader.GetStoreOriginalJSONForExtrasAndExtensions();

    // Test WriteGltfSceneToFile
    loader.WriteGltfSceneToFile(&model, "./dummy_file", false, false, true, false);

    return 0;
}