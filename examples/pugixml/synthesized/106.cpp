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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_106(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.document_element();
    if (root.empty()) return 0;

    // Test pugi::xml_node::empty
    bool isEmpty = root.empty();

    // Test pugi::xml_node::append_copy
    pugi::xml_node copiedNode = root.append_copy(root);

    // Test pugi::xml_node::remove_children
    bool removedChildren = root.remove_children();

    // Test pugi::xml_node::remove_child (overload 1)
    std::string_view childName = "child";
    bool removedChildByName = root.remove_child(childName);

    // Test pugi::xml_node::remove_child (overload 2)
    const char* childNameCStr = "child";
    bool removedChildByCStr = root.remove_child(childNameCStr);

    // Test pugi::xml_node::remove_attribute
    std::string_view attrName = "attr";
    bool removedAttribute = root.remove_attribute(attrName);

    return 0;
}