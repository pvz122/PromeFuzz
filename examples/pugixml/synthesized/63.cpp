// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::set_name at pugixml.cpp:5984:30 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5974:30 in pugixml.hpp
// pugi::xml_node::set_value at pugixml.cpp:6016:30 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7044:30 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7037:30 in pugixml.hpp
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
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_63(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_node node;
    pugi::xml_attribute attr;
    pugi::xml_text text;

    std::string_view sv(reinterpret_cast<const char*>(Data), Size);

    node.set_name(sv.data(), sv.size());
    node.set_name(sv.data());

    node.set_value(sv.data(), sv.size());

    text.set(sv.data(), sv.size());
    text.set(sv.data());

    attr.set_value(static_cast<unsigned long>(Size));

    return 0;
}