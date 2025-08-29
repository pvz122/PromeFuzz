// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::name at pugixml.cpp:5362:44 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5486:35 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5463:35 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5456:35 in pugixml.hpp
// pugi::xml_attribute::value at pugixml.cpp:5369:44 in pugixml.hpp
// pugi::xml_attribute::as_string at pugixml.cpp:5299:44 in pugixml.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <pugixml.hpp>
#include <cstdint>
#include <cstring>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");
    pugi::xml_attribute attr = node.append_attribute("attr");

    // Use the first byte to determine the operation
    uint8_t operation = Data[0] % 5;
    size_t dataSize = Size - 1;
    const uint8_t* data = Data + 1;

    // Ensure the data is null-terminated
    std::vector<char> buffer(dataSize + 1);
    std::memcpy(buffer.data(), data, dataSize);
    buffer[dataSize] = '\0';

    switch (operation) {
        case 0: {
            // Test pugi::xml_attribute::name
            attr.name();
            break;
        }
        case 1: {
            // Test pugi::xml_attribute::set_value
            attr.set_value(buffer.data(), dataSize);
            break;
        }
        case 2: {
            // Test pugi::xml_attribute::set_name with both overloads
            attr.set_name(buffer.data(), dataSize);
            attr.set_name(buffer.data());
            break;
        }
        case 3: {
            // Test pugi::xml_attribute::value
            attr.value();
            break;
        }
        case 4: {
            // Test pugi::xml_attribute::as_string
            attr.as_string(buffer.data());
            break;
        }
        default:
            break;
    }

    return 0;
}