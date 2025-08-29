// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::find_child_by_attribute at pugixml.cpp:6663:34 in pugixml.hpp
// pugi::xml_node::find_child_by_attribute at pugixml.cpp:6688:34 in pugixml.hpp
// pugi::xml_node::find_child_by_attribute at pugixml.cpp:6663:34 in pugixml.hpp
// pugi::xml_node::find_child_by_attribute at pugixml.cpp:6688:34 in pugixml.hpp
// pugi::xml_node::find_child_by_attribute at pugixml.cpp:6663:34 in pugixml.hpp
// pugi::xml_node::find_child_by_attribute at pugixml.cpp:6688:34 in pugixml.hpp
// pugi::xml_node::find_child_by_attribute at pugixml.cpp:6663:34 in pugixml.hpp
// pugi::xml_node::find_child_by_attribute at pugixml.cpp:6688:34 in pugixml.hpp
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
#include <cstddef>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");

    // Append child nodes
    root.append_child(pugi::node_element);
    root.append_child("child1");
    root.append_child(pugi::node_comment);
    root.append_child("child2");

    // Append attributes
    root.append_attribute("attr1");
    root.append_attribute("attr2");
    root.append_attribute("attr3");

    // Find child by attribute
    root.find_child_by_attribute("child1", "attr1", "value1");
    root.find_child_by_attribute("attr1", "value1");
    root.find_child_by_attribute("child2", "attr2", "value2");
    root.find_child_by_attribute("attr2", "value2");
    root.find_child_by_attribute("child1", "attr3", "value3");
    root.find_child_by_attribute("attr3", "value3");
    root.find_child_by_attribute("child2", "attr1", "value1");
    root.find_child_by_attribute("attr1", "value1");

    return 0;
}