// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::insert_child_before at pugixml.cpp:6347:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_child_before at pugixml.cpp:6347:34 in pugixml.hpp
// pugi::xml_node::insert_child_before at pugixml.cpp:6347:34 in pugixml.hpp
// pugi::xml_node::insert_child_before at pugixml.cpp:6347:34 in pugixml.hpp
// pugi::xml_node::insert_child_before at pugixml.cpp:6384:34 in pugixml.hpp
// pugi::xml_node::insert_child_before at pugixml.cpp:6384:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");
    pugi::xml_node node1 = root.append_child("node1");
    pugi::xml_node node2 = root.append_child("node2");

    // Ensure the input data is null-terminated
    std::vector<char> buffer(Size + 1);
    std::memcpy(buffer.data(), Data, Size);
    buffer[Size] = '\0';

    std::string_view name1(buffer.data(), Size / 2);
    std::string_view name2(buffer.data() + Size / 2, Size - Size / 2);

    pugi::xml_node inserted1 = root.insert_child_before(name1.data(), node1);
    pugi::xml_node child1 = root.child(name1.data());
    pugi::xml_node child2 = root.child(name2.data());
    pugi::xml_node child3 = root.child("node1");
    pugi::xml_node inserted2 = root.insert_child_before(name2.data(), node2);
    pugi::xml_node inserted3 = root.insert_child_before("node3", node1);
    pugi::xml_node inserted4 = root.insert_child_before("node4", node2);
    pugi::xml_node inserted5 = root.insert_child_before(name1, node1);
    pugi::xml_node inserted6 = root.insert_child_before(name2, node2);

    return 0;
}