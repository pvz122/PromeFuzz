// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5974:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5984:30 in pugixml.hpp
// pugi::xml_node::path at pugixml.cpp:6708:34 in pugixml.hpp
// pugi::xml_node::name at pugixml.cpp:5685:39 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::parent at pugixml.cpp:5910:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_element_by_path at pugixml.cpp:6745:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child(pugi::node_element);
    root.set_name("root");

    pugi::xml_node child = root.append_child(pugi::node_element);
    child.set_name(reinterpret_cast<const char*>(Data), Size);

    // Test pugi::xml_node::path
    child.path();

    // Test pugi::xml_node::name
    child.name();

    // Test pugi::xml_node::append_child
    child.append_child(pugi::node_element);

    // Test pugi::xml_node::parent
    child.parent();

    // Test pugi::xml_node::first_child
    child.first_child();

    // Test pugi::xml_node::first_element_by_path
    child.first_element_by_path("root/child");

    return 0;
}