// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::children at pugixml.cpp:5635:61 in pugixml.hpp
// pugi::xml_node::begin at pugixml.cpp:5615:44 in pugixml.hpp
// pugi::xml_node::end at pugixml.cpp:5620:44 in pugixml.hpp
// pugi::xml_node::children at pugixml.cpp:5635:61 in pugixml.hpp
// pugi::xml_object_range::begin at pugixml.hpp:337:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::attributes at pugixml.cpp:5645:66 in pugixml.hpp
// pugi::xml_node::attributes_begin at pugixml.cpp:5625:54 in pugixml.hpp
// pugi::xml_node::attributes_end at pugixml.cpp:5630:54 in pugixml.hpp
// pugi::xml_node::attributes at pugixml.cpp:5645:66 in pugixml.hpp
// pugi::xml_object_range::begin at pugixml.hpp:337:6 in pugixml.hpp
// pugi::xml_object_range::end at pugixml.hpp:338:6 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    auto children = root.children();
    auto begin = root.begin();
    auto end = root.end();
    auto children_range = root.children();
    auto range_begin = children_range.begin();
    auto range_end = children_range.end();
    auto child = root.child("child");
    auto attributes = root.attributes();
    auto attributes_begin = root.attributes_begin();
    auto attributes_end = root.attributes_end();
    auto attributes_range = root.attributes();
    auto attributes_range_begin = attributes_range.begin();
    auto attributes_range_end = attributes_range.end();

    return 0;
}