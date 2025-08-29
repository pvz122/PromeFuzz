// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::empty at pugixml.cpp:5680:30 in pugixml.hpp
// pugi::xml_node::empty at pugixml.cpp:5680:30 in pugixml.hpp
// pugi::xml_node::append_copy at pugixml.cpp:6394:34 in pugixml.hpp
// pugi::xml_node::remove_children at pugixml.cpp:6604:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6585:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6579:30 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6538:30 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_102(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.document_element();
    if (root.empty()) return 0;

    // Test pugi::xml_node::empty
    bool is_empty = root.empty();

    // Test pugi::xml_node::append_copy
    pugi::xml_node copied_node = root.append_copy(root);

    // Test pugi::xml_node::remove_children
    bool children_removed = root.remove_children();

    // Test pugi::xml_node::remove_child
    std::string_view child_name = "child";
    bool child_removed_by_name = root.remove_child(child_name);
    bool child_removed_by_char = root.remove_child("child");

    // Test pugi::xml_node::remove_attribute
    std::string_view attr_name = "attr";
    bool attr_removed = root.remove_attribute(attr_name);

    return 0;
}