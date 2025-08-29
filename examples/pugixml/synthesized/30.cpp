// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::hash_value at pugixml.cpp:6833:32 in pugixml.hpp
// pugi::xml_attribute::hash_value at pugixml.cpp:5376:37 in pugixml.hpp
// pugi::xml_node::hash_value at pugixml.cpp:6833:32 in pugixml.hpp
// pugi::xml_node::hash_value at pugixml.cpp:6833:32 in pugixml.hpp
// pugi::xml_node::hash_value at pugixml.cpp:6833:32 in pugixml.hpp
// pugi::xml_node::hash_value at pugixml.cpp:6833:32 in pugixml.hpp
// pugi::xml_attribute::hash_value at pugixml.cpp:5376:37 in pugixml.hpp
// pugi::xml_node::hash_value at pugixml.cpp:6833:32 in pugixml.hpp
// pugi::xml_attribute::hash_value at pugixml.cpp:5376:37 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    std::string_view childName(reinterpret_cast<const char*>(Data), Size % 20);
    pugi::xml_node childNode = root.child(childName.data());

    pugi::xml_attribute firstAttr = root.first_attribute();
    pugi::xml_node firstChild = root.first_child();

    if (childNode) {
        childNode.hash_value();
    }

    if (firstAttr) {
        firstAttr.hash_value();
    }

    if (firstChild) {
        firstChild.hash_value();
    }

    root.hash_value();
    root.hash_value();
    root.hash_value();

    if (firstAttr) {
        firstAttr.hash_value();
    }

    root.hash_value();

    if (firstAttr) {
        firstAttr.hash_value();
    }

    return 0;
}