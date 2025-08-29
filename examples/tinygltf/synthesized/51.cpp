// This fuzz driver is generated for library tinygltf, aiming to fuzz the following functions:
// tinygltf::TinyGLTF::GetImagesAsIs at tiny_gltf.h:1554:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetImagesAsIs at tiny_gltf.h:1550:8 in tiny_gltf.h
// tinygltf::TinyGLTF::GetPreserveImageChannels at tiny_gltf.h:1545:8 in tiny_gltf.h
// tinygltf::TinyGLTF::GetSerializeDefaultValues at tiny_gltf.h:1522:8 in tiny_gltf.h
// tinygltf::TinyGLTF::SetSerializeDefaultValues at tiny_gltf.h:1518:8 in tiny_gltf.h
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
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;

    // Set up the model with some dummy data
    model.asset.version = "2.0";
    model.asset.generator = "FuzzTest";
    model.scenes.emplace_back();
    model.scenes[0].nodes.push_back(0);
    model.nodes.emplace_back();
    model.meshes.emplace_back();
    model.materials.emplace_back();
    model.buffers.emplace_back();
    model.bufferViews.emplace_back();
    model.accessors.emplace_back();
    model.images.emplace_back();
    model.textures.emplace_back();
    model.samplers.emplace_back();
    model.skins.emplace_back();
    model.animations.emplace_back();
    model.cameras.emplace_back();
    model.lights.emplace_back();
    model.audioSources.emplace_back();
    model.audioEmitters.emplace_back();

    // Test GetImagesAsIs and SetImagesAsIs
    bool imagesAsIs = loader.GetImagesAsIs();
    loader.SetImagesAsIs(!imagesAsIs);

    // Test GetPreserveImageChannels
    bool preserveChannels = loader.GetPreserveImageChannels();

    // Test SetSerializeDefaultValues and GetSerializeDefaultValues
    bool serializeDefaults = loader.GetSerializeDefaultValues();
    loader.SetSerializeDefaultValues(!serializeDefaults);

    // Test WriteGltfSceneToFile
    std::string filename = "./dummy_file.gltf";
    bool embedImages = Size % 2 == 0;
    bool embedBuffers = Size % 3 == 0;
    bool prettyPrint = Size % 4 == 0;
    bool writeBinary = Size % 5 == 0;
    loader.WriteGltfSceneToFile(&model, filename, embedImages, embedBuffers, prettyPrint, writeBinary);

    // Clean up
    std::remove(filename.c_str());

    return 0;
}