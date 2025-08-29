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

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;

    // Initialize model with some data
    model.asset.version = "2.0";
    model.buffers.push_back(tinygltf::Buffer());
    model.bufferViews.push_back(tinygltf::BufferView());
    model.accessors.push_back(tinygltf::Accessor());
    model.meshes.push_back(tinygltf::Mesh());
    model.materials.push_back(tinygltf::Material());
    model.textures.push_back(tinygltf::Texture());
    model.images.push_back(tinygltf::Image());
    model.skins.push_back(tinygltf::Skin());
    model.samplers.push_back(tinygltf::Sampler());
    model.cameras.push_back(tinygltf::Camera());
    model.scenes.push_back(tinygltf::Scene());
    model.lights.push_back(tinygltf::Light());
    model.audioEmitters.push_back(tinygltf::AudioEmitter());
    model.audioSources.push_back(tinygltf::AudioSource());

    // Test WriteGltfSceneToStream
    std::ostringstream oss;
    bool prettyPrint = Size % 2 == 0;
    bool writeBinary = Size % 3 == 0;
    loader.WriteGltfSceneToStream(&model, oss, prettyPrint, writeBinary);

    // Test GetSerializeDefaultValues
    bool serializeDefaults = loader.GetSerializeDefaultValues();

    // Test SetStoreOriginalJSONForExtrasAndExtensions
    bool storeOriginalJSON = Size % 4 == 0;
    loader.SetStoreOriginalJSONForExtrasAndExtensions(storeOriginalJSON);

    // Test SetSerializeDefaultValues
    bool newSerializeDefaults = Size % 5 == 0;
    loader.SetSerializeDefaultValues(newSerializeDefaults);

    // Test GetStoreOriginalJSONForExtrasAndExtensions
    bool currentStoreOriginalJSON = loader.GetStoreOriginalJSONForExtrasAndExtensions();

    // Test WriteGltfSceneToFile
    std::string filename = "./dummy_file";
    bool embedImages = Size % 6 == 0;
    bool embedBuffers = Size % 7 == 0;
    loader.WriteGltfSceneToFile(&model, filename, embedImages, embedBuffers, prettyPrint, writeBinary);

    return 0;
}