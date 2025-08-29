// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::insert_child_after at pugixml.cpp:6338:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_child_after at pugixml.cpp:6338:34 in pugixml.hpp
// pugi::xml_node::insert_child_after at pugixml.cpp:6338:34 in pugixml.hpp
// pugi::xml_node::insert_child_after at pugixml.cpp:6338:34 in pugixml.hpp
// pugi::xml_node::insert_child_after at pugixml.cpp:6338:34 in pugixml.hpp
// pugi::xml_node::insert_child_after at pugixml.cpp:6338:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");
    pugi::xml_node node1 = root.append_child("node1");
    pugi::xml_node node2 = root.append_child("node2");

    std::string name(reinterpret_cast<const char*>(Data), Size);

    pugi::xml_node inserted1 = root.insert_child_after(name.c_str(), node1);
    pugi::xml_node child1 = root.child("node1");
    pugi::xml_node child2 = root.child("node2");
    pugi::xml_node child3 = root.child(name.c_str());
    pugi::xml_node inserted2 = root.insert_child_after(name.c_str(), node2);
    pugi::xml_node inserted3 = root.insert_child_after(name.c_str(), inserted1);
    pugi::xml_node inserted4 = root.insert_child_after(name.c_str(), inserted2);
    pugi::xml_node inserted5 = root.insert_child_after(name.c_str(), inserted3);
    pugi::xml_node inserted6 = root.insert_child_after(name.c_str(), inserted4);

    return 0;
}