// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6532:30 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
// pugi::xml_attribute::name at pugixml.cpp:5362:44 in pugixml.hpp
// pugi::xml_node::remove_attribute at pugixml.cpp:6544:30 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
// pugi::xml_node::remove_attributes at pugixml.cpp:6558:30 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6579:30 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::name at pugixml.cpp:5685:39 in pugixml.hpp
// pugi::xml_node::remove_children at pugixml.cpp:6604:30 in pugixml.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <pugixml.hpp>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.root().first_child();
    if (!root) return 0;

    // Remove attributes
    if (root.first_attribute()) {
        root.remove_attribute(root.first_attribute().name());
        root.remove_attribute(root.first_attribute());
    }

    // Remove all attributes
    root.remove_attributes();

    // Remove child nodes
    if (root.first_child()) {
        root.remove_child(root.first_child().name());
    }

    // Remove all child nodes
    root.remove_children();

    return 0;
}