// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5530:35 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5479:35 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5544:35 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5558:35 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5479:35 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5530:35 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");

    std::string name1(reinterpret_cast<const char*>(Data), 5);
    std::string name2(reinterpret_cast<const char*>(Data + 5), 5);

    pugi::xml_attribute attr1 = node.append_attribute(name1.c_str());
    attr1.set_value(1.23);

    pugi::xml_attribute attr2 = node.append_attribute(name2.c_str());
    attr2.set_value("test");

    pugi::xml_attribute attr3 = node.append_attribute(name1.c_str());
    attr3.set_value(4.56f);

    pugi::xml_attribute attr4 = node.append_attribute(name2.c_str());
    attr4.set_value(true);

    pugi::xml_attribute attr5 = node.append_attribute(name1.c_str());
    attr5.set_value("another_test");

    pugi::xml_attribute attr6 = node.append_attribute(name2.c_str());
    attr6.set_value(7.89);

    return 0;
}