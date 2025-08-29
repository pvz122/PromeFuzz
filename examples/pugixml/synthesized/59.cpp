// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::last_attribute at pugixml.cpp:5954:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_after at pugixml.cpp:6072:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6232:39 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5780:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");

    // Append some attributes
    pugi::xml_attribute attr1 = node.append_attribute("attr1");
    pugi::xml_attribute attr2 = node.append_attribute("attr2");

    // Test last_attribute
    pugi::xml_attribute last_attr = node.last_attribute();

    // Test insert_attribute_after
    std::string_view attr_name = "new_attr";
    pugi::xml_attribute new_attr = node.insert_attribute_after(attr_name.data(), attr1);

    // Test append_attribute
    pugi::xml_attribute appended_attr = node.append_attribute("appended_attr");

    // Test insert_copy_before
    pugi::xml_attribute copied_attr = node.insert_copy_before(attr1, attr2);

    // Test first_attribute
    pugi::xml_attribute first_attr = node.first_attribute();

    // Test attribute
    std::string_view attr_name_to_find = "attr1";
    pugi::xml_attribute found_attr = node.attribute(attr_name_to_find);

    return 0;
}