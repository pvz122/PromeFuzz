// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7037:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7037:30 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7044:30 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7044:30 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7044:30 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7044:30 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");
    pugi::xml_node child1 = root.append_child("child1");
    pugi::xml_node child2 = root.append_child("child2");
    child1.append_child("subchild1").text().set("value1");
    child2.append_child("subchild2").text().set("value2");

    std::string_view str(reinterpret_cast<const char*>(Data), Size);

    pugi::xml_node node = root.child("child1");
    pugi::xml_text text = node.text();
    text.set(str.data(), str.size());

    node = root.first_child();
    text = node.text();
    text.set(str.data(), str.size());

    node = root.first_child();
    node = root.last_child();
    text = node.text();
    text.set(str.data(), str.size());

    node = root.first_child();
    node = root.last_child();
    text = node.text();
    text.set(str.data(), str.size());

    node = root.first_child();

    return 0;
}