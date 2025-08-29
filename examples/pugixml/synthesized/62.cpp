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
#include "pugixml.hpp"
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");
    pugi::xml_attribute attr = node.append_attribute("attr");

    // Ensure the string is null-terminated
    std::vector<char> str_data(Data + 1, Data + Size);
    str_data.push_back('\0');
    const char* str = str_data.data();

    // Use the first byte to determine the operation
    uint8_t operation = Data[0] % 6;

    switch (operation) {
        case 0:
            attr.name();
            break;
        case 1:
            attr.set_value(str);
            break;
        case 2:
            attr.as_string(str);
            break;
        case 3:
            node.attribute(str);
            break;
        case 4:
            attr.value();
            break;
        case 5:
            attr.set_name(str);
            break;
        default:
            break;
    }

    return 0;
}