// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5551:35 in pugixml.hpp
// pugi::xml_attribute::as_double at pugixml.cpp:5320:37 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5537:35 in pugixml.hpp
// pugi::xml_attribute::as_double at pugixml.cpp:5320:37 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5551:35 in pugixml.hpp
// pugi::xml_attribute::as_double at pugixml.cpp:5320:37 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7095:30 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7109:30 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7095:30 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");

    pugi::xml_node child = root.append_child("child");
    pugi::xml_attribute attr = child.append_attribute("attr");

    attr.set_value(1.23f, 2);
    attr.as_double();

    attr.set_value(4.56, 3);
    attr.as_double();

    attr.set_value(7.89f, 2);
    attr.as_double();

    pugi::xml_text text = child.text();
    text.set(1.23f, 2);

    text = child.text();
    text = child.text();
    text.set(4.56, 3);

    text = child.text();
    text = child.text();
    text.set(7.89f, 2);

    text = child.text();

    return 0;
}