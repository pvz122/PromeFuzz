// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7074:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7081:30 in pugixml.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <pugixml.hpp>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");

    std::string name1(reinterpret_cast<const char*>(Data), std::min(Size, static_cast<size_t>(100)));
    std::string name2(reinterpret_cast<const char*>(Data + Size / 2), std::min(Size - Size / 2, static_cast<size_t>(100)));

    pugi::xml_node child1 = root.child(name1.c_str());
    pugi::xml_node child2 = root.append_child(name1.c_str());
    pugi::xml_node child3 = root.append_child(name2.c_str());

    pugi::xml_text text1 = child2.text();
    text1.set(static_cast<long>(Size));

    pugi::xml_node child4 = root.append_child(name1.c_str());
    pugi::xml_node child5 = root.append_child(name2.c_str());

    pugi::xml_text text2 = child5.text();
    text2.set(static_cast<unsigned long>(Size));

    return 0;
}