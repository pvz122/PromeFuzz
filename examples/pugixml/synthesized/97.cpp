// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_text::set at pugixml.cpp:7116:30 in pugixml.hpp
// pugi::xml_node::empty at pugixml.cpp:5680:30 in pugixml.hpp
// pugi::xml_attribute::empty at pugixml.cpp:5357:35 in pugixml.hpp
// pugi::xml_node::begin at pugixml.cpp:5615:44 in pugixml.hpp
// pugi::xml_node::end at pugixml.cpp:5620:44 in pugixml.hpp
// pugi::xml_object_range::empty at pugixml.hpp:340:8 in pugixml.hpp
// pugi::xml_text::as_bool at pugixml.cpp:7011:30 in pugixml.hpp
// pugi::xml_text::empty at pugixml.cpp:6958:30 in pugixml.hpp
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
#include <cstdlib>
#include <cstring>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize pugi::xml_text
    pugi::xml_text text;
    bool value = Data[0] % 2 == 0;
    text.set(value);

    // Initialize pugi::xml_node
    pugi::xml_node node;
    bool isNodeEmpty = node.empty();

    // Initialize pugi::xml_attribute
    pugi::xml_attribute attr;
    bool isAttrEmpty = attr.empty();

    // Initialize pugi::xml_object_range
    pugi::xml_object_range<pugi::xml_node_iterator> range(node.begin(), node.end());
    bool isRangeEmpty = range.empty();

    // Test pugi::xml_text::as_bool
    bool asBool = text.as_bool();

    // Test pugi::xml_text::empty
    bool isTextEmpty = text.empty();

    return 0;
}