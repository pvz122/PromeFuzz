// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::remove_children at pugixml.cpp:6604:30 in pugixml.hpp
// pugi::xml_node::children at pugixml.cpp:5635:61 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::prepend_copy at pugixml.cpp:6411:34 in pugixml.hpp
// pugi::xml_node::attributes at pugixml.cpp:5645:66 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6544:30 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6538:30 in pugixml.hpp
// pugi::xml_node::remove_attributes at pugixml.cpp:6558:30 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_101(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    // Test remove_children
    root.remove_children();

    // Test remove_child
    for (pugi::xml_node child : root.children()) {
        root.remove_child(child);
    }

    // Test prepend_copy
    pugi::xml_node first_child = root.first_child();
    if (first_child) {
        root.prepend_copy(first_child);
    }

    // Test remove_attribute
    for (pugi::xml_attribute attr : root.attributes()) {
        root.remove_attribute(attr);
    }

    // Test remove_attribute with name
    std::string_view attr_name = "test_attr";
    root.remove_attribute(attr_name);

    // Test remove_attributes
    root.remove_attributes();

    return 0;
}