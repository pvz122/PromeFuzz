// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6250:34 in pugixml.hpp
// pugi::xml_node::set_value at pugixml.cpp:6006:30 in pugixml.hpp
// pugi::xml_node::offset_debug at pugixml.cpp:6870:35 in pugixml.hpp
// pugi::xml_node::parent at pugixml.cpp:5910:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5903:34 in pugixml.hpp
// pugi::xml_node::previous_sibling at pugixml.cpp:5903:34 in pugixml.hpp
// pugi::xml_node::type at pugixml.cpp:5692:39 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.root().first_child();
    if (!root) return 0;

    // Test next_sibling
    pugi::xml_node next = root.next_sibling();
    while (next) {
        next = next.next_sibling();
    }

    // Test append_child
    pugi::xml_node new_child = root.append_child(pugi::node_element);
    if (new_child) {
        new_child.append_child(pugi::node_pcdata).set_value("fuzz_data");
    }

    // Test offset_debug
    ptrdiff_t offset = root.offset_debug();

    // Test parent
    pugi::xml_node parent = root.parent();

    // Test previous_sibling
    pugi::xml_node prev = root.previous_sibling();
    while (prev) {
        prev = prev.previous_sibling();
    }

    // Test type
    pugi::xml_node_type node_type = root.type();

    return 0;
}