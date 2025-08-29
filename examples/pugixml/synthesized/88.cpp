// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5995:30 in pugixml.hpp
// pugi::xml_node::set_value at pugixml.cpp:6027:30 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7052:30 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7116:30 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5494:35 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5558:35 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_88(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");
    pugi::xml_attribute attr = node.append_attribute("attr");
    pugi::xml_text text = node.text();

    std::string_view str(reinterpret_cast<const char*>(Data), Size);

    node.set_name(str);
    node.set_value(str);
    text.set(str);
    text.set(Size % 2 == 0);
    attr.set_value(str);
    attr.set_value(Size % 2 == 0);

    return 0;
}