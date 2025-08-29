// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5558:35 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5502:35 in pugixml.hpp
// pugi::xml_attribute::as_bool at pugixml.cpp:5334:35 in pugixml.hpp
// pugi::xml_attribute::empty at pugixml.cpp:5357:35 in pugixml.hpp
// pugi::xml_attribute::as_int at pugixml.cpp:5306:34 in pugixml.hpp
// pugi::xml_attribute::as_uint at pugixml.cpp:5313:43 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_100(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");
    pugi::xml_attribute attr = node.append_attribute("attr");

    // Set value using the first byte of input
    attr.set_value(static_cast<bool>(Data[0] & 1));
    attr.set_value(static_cast<int>(Data[0]));

    // Test as_bool
    bool bool_val = attr.as_bool();

    // Test empty
    bool is_empty = attr.empty();

    // Test as_int
    int int_val = attr.as_int();

    // Test as_uint
    unsigned int uint_val = attr.as_uint();

    return 0;
}