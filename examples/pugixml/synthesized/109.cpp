// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::insert_copy_after at pugixml.cpp:6214:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_after at pugixml.cpp:6072:39 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6180:39 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6232:39 in pugixml.hpp
// pugi::xml_node::insert_attribute_before at pugixml.cpp:6090:39 in pugixml.hpp
// pugi::xml_attribute::name at pugixml.cpp:5362:44 in pugixml.hpp
// pugi::xml_node::find_attribute at pugixml.hpp:683:47 in pugixml.hpp
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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_109(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("root");
    pugi::xml_attribute attr1 = node.append_attribute("attr1");
    pugi::xml_attribute attr2 = node.append_attribute("attr2");

    // Fuzz insert_copy_after
    node.insert_copy_after(attr1, attr2);

    // Fuzz insert_attribute_after
    node.insert_attribute_after("attr3", attr1);

    // Fuzz append_copy
    node.append_copy(attr1);

    // Fuzz insert_copy_before
    node.insert_copy_before(attr1, attr2);

    // Fuzz insert_attribute_before
    node.insert_attribute_before("attr4", attr1);

    // Fuzz find_attribute
    auto pred = [](pugi::xml_attribute attr) { return std::string_view(attr.name()) == "attr1"; };
    node.find_attribute(pred);

    return 0;
}