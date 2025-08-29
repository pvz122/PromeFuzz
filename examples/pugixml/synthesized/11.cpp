// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5479:35 in pugixml.hpp
// pugi::xml_node::insert_attribute_after at pugixml.cpp:6072:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5479:35 in pugixml.hpp
// pugi::xml_node::insert_attribute_before at pugixml.cpp:6090:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5479:35 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6180:39 in pugixml.hpp
// pugi::xml_node::prepend_copy at pugixml.cpp:6197:39 in pugixml.hpp
// pugi::xml_node::insert_copy_after at pugixml.cpp:6214:39 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6232:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_11(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");
    pugi::xml_node node = root.append_child("node");

    pugi::xml_attribute attr1 = node.append_attribute("attr1");
    attr1.set_value("value1");

    pugi::xml_attribute attr2 = node.insert_attribute_after("attr2", attr1);
    attr2.set_value("value2");

    pugi::xml_attribute attr3 = node.insert_attribute_before("attr3", attr1);
    attr3.set_value("value3");

    pugi::xml_node child1 = node.first_child();
    pugi::xml_node child2 = node.first_child();
    pugi::xml_node child3 = node.first_child();
    pugi::xml_node child4 = node.first_child();

    pugi::xml_attribute attr4 = node.append_copy(attr1);
    pugi::xml_attribute attr5 = node.prepend_copy(attr2);
    pugi::xml_attribute attr6 = node.insert_copy_after(attr3, attr1);
    pugi::xml_attribute attr7 = node.insert_copy_before(attr1, attr2);

    return 0;
}