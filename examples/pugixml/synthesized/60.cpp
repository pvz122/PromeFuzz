// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::last_attribute at pugixml.cpp:5954:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6109:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_after at pugixml.cpp:6072:39 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5780:39 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_before at pugixml.cpp:6090:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");

    // Append some attributes
    node.append_attribute("attr1") = "value1";
    node.append_attribute("attr2") = "value2";
    node.append_attribute("attr3") = "value3";

    // Test last_attribute
    pugi::xml_attribute last_attr = node.last_attribute();

    // Test append_attribute
    std::string_view attr_name(reinterpret_cast<const char*>(Data), Size);
    pugi::xml_attribute new_attr = node.append_attribute(attr_name);

    // Test insert_attribute_after
    pugi::xml_attribute attr_to_insert_after = node.attribute("attr1");
    pugi::xml_attribute inserted_attr = node.insert_attribute_after("new_attr", attr_to_insert_after);

    // Test first_attribute
    pugi::xml_attribute first_attr = node.first_attribute();

    // Test attribute
    pugi::xml_attribute found_attr = node.attribute(attr_name);

    // Test insert_attribute_before
    pugi::xml_attribute attr_to_insert_before = node.attribute("attr2");
    pugi::xml_attribute inserted_before_attr = node.insert_attribute_before("new_attr_before", attr_to_insert_before);

    return 0;
}