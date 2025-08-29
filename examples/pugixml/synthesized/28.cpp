// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5516:35 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5523:35 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5516:35 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5523:35 in pugixml.hpp
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
#include <stdint.h>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");

    std::string_view child_name(reinterpret_cast<const char*>(Data), Size);
    pugi::xml_node child_node = root.child(child_name.data());

    pugi::xml_attribute attr1 = child_node.append_attribute("attr1");
    pugi::xml_attribute attr2 = child_node.append_attribute("attr2");

    attr1.set_value(static_cast<long>(Size));
    attr2.set_value(static_cast<unsigned long>(Size));

    pugi::xml_attribute attr3 = child_node.append_attribute("attr3");
    pugi::xml_attribute attr4 = child_node.append_attribute("attr4");

    attr3.set_value(static_cast<long>(Size));
    attr4.set_value(static_cast<unsigned long>(Size));

    return 0;
}