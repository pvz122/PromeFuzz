// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_after at pugixml.cpp:6143:39 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6180:39 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6232:39 in pugixml.hpp
// pugi::xml_node::prepend_attribute at pugixml.cpp:6055:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_before at pugixml.cpp:6161:39 in pugixml.hpp
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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("root");
    pugi::xml_attribute attr = node.append_attribute("name");

    // Ensure the name is null-terminated
    std::string name(reinterpret_cast<const char*>(Data), Size);
    std::string_view name_view(name);

    // Test insert_attribute_after
    node.insert_attribute_after(name_view, attr);

    // Test append_copy
    node.append_copy(attr);

    // Test insert_copy_before
    node.insert_copy_before(attr, attr);

    // Test prepend_attribute
    node.prepend_attribute(name.c_str());

    // Test attribute
    node.attribute(name.c_str());

    // Test insert_attribute_before
    node.insert_attribute_before(name_view, attr);

    return 0;
}