// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::last_attribute at pugixml.cpp:5954:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
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
#include <stdint.h>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.root();
    if (!root) return 0;

    size_t attr_name_length = Size % 32;
    size_t child_name_length = Size % 32;
    if (attr_name_length == 0) attr_name_length = 1;
    if (child_name_length == 0) child_name_length = 1;

    // Ensure we don't read beyond the input buffer
    if (attr_name_length > Size) attr_name_length = Size;
    if (child_name_length > Size - attr_name_length) child_name_length = Size - attr_name_length;

    std::string attr_name(reinterpret_cast<const char*>(Data), attr_name_length);
    std::string child_name(reinterpret_cast<const char*>(Data + attr_name_length), child_name_length);

    pugi::xml_attribute attr1 = root.attribute(attr_name.c_str());
    pugi::xml_node child = root.child(child_name.c_str());
    pugi::xml_attribute attr2 = root.attribute(attr_name.c_str());
    pugi::xml_attribute attr3 = root.attribute(attr_name.c_str());
    pugi::xml_attribute attr4 = root.attribute(attr_name.c_str());
    pugi::xml_attribute last_attr = root.last_attribute();
    pugi::xml_attribute attr5 = root.attribute(attr_name.c_str());
    pugi::xml_attribute attr6 = root.attribute(attr_name.c_str());

    return 0;
}