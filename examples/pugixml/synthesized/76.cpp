// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::find_node at pugixml.hpp:707:42 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::find_child at pugixml.hpp:695:42 in pugixml.hpp
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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_76(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.root().first_child();
    if (!root) return 0;

    // Test find_node
    auto pred = [](pugi::xml_node node) { return true; };
    root.find_node(pred);

    // Test append_child
    root.append_child(pugi::node_element);

    // Test find_child
    root.find_child(pred);

    // Test parent
    root.parent();

    // Test first_child
    root.first_child();

    // Test first_element_by_path
    root.first_element_by_path("path/to/node");

    return 0;
}