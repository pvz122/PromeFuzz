// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::append_child at pugixml.cpp:6320:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_after at pugixml.cpp:6428:34 in pugixml.hpp
// pugi::xml_node::insert_copy_after at pugixml.cpp:6428:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_after at pugixml.cpp:6428:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::name at pugixml.cpp:5685:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_after at pugixml.cpp:6428:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::value at pugixml.cpp:5697:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_after at pugixml.cpp:6428:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::value at pugixml.cpp:5697:39 in pugixml.hpp
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
#include <stdint.h>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("root");

    pugi::xml_node child1 = root.append_child("child1");
    pugi::xml_node child2 = root.append_child("child2");
    pugi::xml_node child3 = root.append_child("child3");

    pugi::xml_node node1 = root.child("child1");
    pugi::xml_node node2 = root.child("child2");
    pugi::xml_node node3 = root.child("child3");

    pugi::xml_node inserted1 = root.insert_copy_after(node1, node2);
    pugi::xml_node inserted2 = root.insert_copy_after(node2, node3);

    pugi::xml_node node4 = root.child("child1");
    pugi::xml_node node5 = root.child("child2");
    pugi::xml_node node6 = root.child("child3");

    pugi::xml_node inserted3 = root.insert_copy_after(node4, node5);
    pugi::xml_node node7 = root.child("child1");
    pugi::xml_node node8 = root.child("child2");
    pugi::xml_node node9 = root.child("child3");

    pugi::xml_node firstChild = root.first_child();
    const char* name = firstChild.name();

    pugi::xml_node node10 = root.child("child1");
    pugi::xml_node inserted4 = root.insert_copy_after(node10, node9);

    pugi::xml_node node11 = root.child("child1");
    pugi::xml_node firstChild2 = root.first_child();
    pugi::xml_node node12 = root.child("child1");
    pugi::xml_node lastChild = root.last_child();
    const char* value = lastChild.value();

    pugi::xml_node node13 = root.child("child1");
    pugi::xml_node inserted5 = root.insert_copy_after(node13, lastChild);

    pugi::xml_node node14 = root.child("child1");
    pugi::xml_node firstChild3 = root.first_child();
    pugi::xml_node node15 = root.child("child1");
    pugi::xml_node firstChild4 = root.first_child();
    const char* value2 = firstChild4.value();

    return 0;
}