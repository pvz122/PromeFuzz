// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_attribute at pugixml.cpp:5948:39 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::internal_object at pugixml.cpp:6838:42 in pugixml.hpp
// pugi::xml_attribute::internal_object at pugixml.cpp:5381:52 in pugixml.hpp
// pugi::xml_node::internal_object at pugixml.cpp:6838:42 in pugixml.hpp
// pugi::xml_node::internal_object at pugixml.cpp:6838:42 in pugixml.hpp
// pugi::xml_node::internal_object at pugixml.cpp:6838:42 in pugixml.hpp
// pugi::xml_node::internal_object at pugixml.cpp:6838:42 in pugixml.hpp
// pugi::xml_attribute::internal_object at pugixml.cpp:5381:52 in pugixml.hpp
// pugi::xml_node::internal_object at pugixml.cpp:6838:42 in pugixml.hpp
// pugi::xml_attribute::internal_object at pugixml.cpp:5381:52 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    pugi::xml_node childNode = root.child("child");
    pugi::xml_attribute firstAttr = root.first_attribute();
    pugi::xml_node firstChild = root.first_child();

    childNode.internal_object();
    firstAttr.internal_object();
    firstChild.internal_object();

    root.internal_object();
    root.internal_object();
    root.internal_object();

    firstAttr.internal_object();
    root.internal_object();
    firstAttr.internal_object();

    return 0;
}