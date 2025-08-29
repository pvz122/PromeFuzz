// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7067:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7102:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7088:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7060:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7116:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7067:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7102:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7088:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7060:30 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::text at pugixml.cpp:5920:34 in pugixml.hpp
// pugi::xml_text::set at pugixml.cpp:7116:30 in pugixml.hpp
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
#include <cstdint>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");

    pugi::xml_node node1 = root.append_child("node1");
    pugi::xml_node node2 = root.append_child("node2");

    node1.text().set(static_cast<unsigned int>(Data[0]));
    pugi::xml_node node3 = root.append_child("node3");
    pugi::xml_node node4 = root.append_child("node4");

    node2.text().set(static_cast<double>(Data[0]));
    pugi::xml_node node5 = root.append_child("node5");

    node3.text().set(static_cast<float>(Data[0]));
    pugi::xml_node node6 = root.append_child("node6");

    node4.text().set(static_cast<int>(Data[0]));
    pugi::xml_node node7 = root.append_child("node7");

    node5.text().set(static_cast<bool>(Data[0] % 2));
    pugi::xml_node node8 = root.append_child("node8");

    node6.text().set(static_cast<unsigned int>(Data[0]));
    pugi::xml_node node9 = root.append_child("node9");

    node7.text().set(static_cast<double>(Data[0]));
    pugi::xml_node node10 = root.append_child("node10");

    node8.text().set(static_cast<float>(Data[0]));
    pugi::xml_node node11 = root.append_child("node11");

    node9.text().set(static_cast<int>(Data[0]));
    pugi::xml_node node12 = root.append_child("node12");

    node10.text().set(static_cast<bool>(Data[0] % 2));

    return 0;
}