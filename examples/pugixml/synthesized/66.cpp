// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::name at pugixml.cpp:5362:44 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5479:35 in pugixml.hpp
// pugi::xml_attribute::as_string at pugixml.cpp:5299:44 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_attribute::value at pugixml.cpp:5369:44 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5456:35 in pugixml.hpp
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
#include <stdint.h>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");
    pugi::xml_attribute attr = node.append_attribute("attr");

    // Ensure the input data is null-terminated
    std::vector<char> buffer(Size + 1);
    std::memcpy(buffer.data(), Data, Size);
    buffer[Size] = '\0';

    // Fuzz pugi::xml_attribute::name
    const char* name = attr.name();

    // Fuzz pugi::xml_attribute::set_value
    attr.set_value(buffer.data());

    // Fuzz pugi::xml_attribute::as_string
    const char* attr_value = attr.as_string();

    // Fuzz pugi::xml_node::attribute
    pugi::xml_attribute found_attr = node.attribute("attr");

    // Fuzz pugi::xml_attribute::value
    const char* attr_value2 = attr.value();

    // Fuzz pugi::xml_attribute::set_name
    attr.set_name(buffer.data());

    return 0;
}