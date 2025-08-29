// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_attribute at pugixml.cpp:6038:39 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5984:30 in pugixml.hpp
// pugi::xml_node::set_name at pugixml.cpp:5974:30 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5463:35 in pugixml.hpp
// pugi::xml_attribute::set_name at pugixml.cpp:5456:35 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5523:35 in pugixml.hpp
// pugi::xml_attribute::set_value at pugixml.cpp:5516:35 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_90(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node node = doc.append_child("node");
    pugi::xml_attribute attr = node.append_attribute("attr");

    // Ensure the input data is null-terminated
    std::vector<char> buffer(Size + 1);
    std::memcpy(buffer.data(), Data, Size);
    buffer[Size] = '\0';

    std::string_view name(buffer.data(), Size);
    std::string_view value(buffer.data(), Size);

    node.set_name(name.data(), name.size());
    node.set_name(name.data());

    attr.set_name(name.data(), name.size());
    attr.set_name(name.data());

    attr.set_value(static_cast<unsigned long>(Size));
    attr.set_value(static_cast<long>(Size));

    return 0;
}