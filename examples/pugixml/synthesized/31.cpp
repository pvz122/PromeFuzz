// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6585:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6579:30 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5766:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6585:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6579:30 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6591:30 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5766:34 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6585:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6579:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6579:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6579:30 in pugixml.hpp
// pugi::xml_node::remove_child at pugixml.cpp:6579:30 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");
    pugi::xml_node child1 = root.append_child("child1");
    pugi::xml_node child2 = root.append_child("child2");
    pugi::xml_node child3 = root.append_child("child3");

    std::string_view name1 = "child1";
    std::string_view name2 = "child2";
    std::string_view name3 = "child3";

    root.remove_child(child1);
    root.remove_child(name1);
    root.remove_child("child1");

    root.child("child2");
    root.child(name2);

    root.remove_child(child2);
    root.remove_child(name2);
    root.remove_child("child2");

    root.child("child3");
    root.remove_child(child3);
    root.child(name3);
    root.remove_child(name3);
    root.remove_child("child3");
    root.remove_child("child3");
    root.remove_child("child3");
    root.remove_child("child3");

    return 0;
}