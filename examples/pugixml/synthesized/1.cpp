// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5479:35 in pugixml.hpp
// pugi::xml_attribute::as_string at pugixml.cpp:5299:44 in pugixml.hpp
// pugi::xml_attribute::as_int at pugixml.cpp:5306:34 in pugixml.hpp
// pugi::xml_attribute::as_uint at pugixml.cpp:5313:43 in pugixml.hpp
// pugi::xml_attribute::as_double at pugixml.cpp:5320:37 in pugixml.hpp
// pugi::xml_attribute::as_float at pugixml.cpp:5327:36 in pugixml.hpp
// pugi::xml_attribute::as_bool at pugixml.cpp:5334:35 in pugixml.hpp
// pugi::xml_attribute::as_llong at pugixml.cpp:5342:40 in pugixml.hpp
// pugi::xml_attribute::as_ullong at pugixml.cpp:5349:49 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");
    pugi::xml_attribute attr = node.append_attribute("attr");

    std::string attr_value(reinterpret_cast<const char*>(Data), Size);
    attr.set_value(attr_value.c_str());

    attr.as_string();
    attr.as_int();
    attr.as_uint();
    attr.as_double();
    attr.as_float();
    attr.as_bool();
    attr.as_llong();
    attr.as_ullong();

    return 0;
}