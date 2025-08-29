// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::name at pugixml.cpp:5685:39 in pugixml.hpp
// pugi::xml_node::find_node at pugixml.hpp:707:42 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::name at pugixml.cpp:5685:39 in pugixml.hpp
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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_72(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.root().first_child();
    if (!root) return 0;

    // Test find_node
    auto pred_node = [](pugi::xml_node node) { return node.name() != nullptr; };
    root.find_node(pred_node);

    // Test append_child
    root.append_child(pugi::node_element);

    // Test find_child
    auto pred_child = [](pugi::xml_node node) { return node.name() != nullptr; };
    root.find_child(pred_child);

    // Test parent
    root.parent();

    // Test first_child
    root.first_child();

    // Test first_element_by_path
    root.first_element_by_path("test.path");

    return 0;
}