// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_string at pugixml.cpp:7709:46 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::type at pugixml.cpp:5692:39 in pugixml.hpp
// pugi::xml_node::value at pugixml.cpp:5697:39 in pugixml.hpp
// pugi::xml_node::type at pugixml.cpp:5692:39 in pugixml.hpp
// pugi::xml_node::value at pugixml.cpp:5697:39 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    pugi::xml_document doc;
    std::string xml_data(reinterpret_cast<const char*>(Data), Size);
    pugi::xml_parse_result result = doc.load_string(xml_data.c_str());

    if (!result) return 0;

    pugi::xml_node root = doc.child("root");
    if (!root) return 0;

    pugi::xml_node child = root.child("child");
    pugi::xml_node first_child = root.first_child();
    pugi::xml_node next_sibling = first_child.next_sibling();
    pugi::xml_node next_sibling_2 = next_sibling.next_sibling();
    pugi::xml_node last_child = root.last_child();
    pugi::xml_node_type type = last_child.type();
    const char* value = last_child.value();
    pugi::xml_node_type type_2 = first_child.type();
    const char* value_2 = first_child.value();
    pugi::xml_node last_child_2 = root.last_child();
    pugi::xml_node first_child_2 = root.first_child();
    pugi::xml_node first_child_3 = root.first_child();

    return 0;
}