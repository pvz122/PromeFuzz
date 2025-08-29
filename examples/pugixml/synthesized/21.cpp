// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6446:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6446:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6446:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::name at pugixml.cpp:5685:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6446:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::name at pugixml.cpp:5685:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::insert_copy_before at pugixml.cpp:6446:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::next_sibling at pugixml.cpp:5746:34 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) return 0;

    pugi::xml_node root = doc.root();
    pugi::xml_node child1 = root.child("child1");
    pugi::xml_node child2 = child1.child("child2");
    pugi::xml_node copied_node = child2.insert_copy_before(child1, child2);
    pugi::xml_node child3 = copied_node.child("child3");
    pugi::xml_node copied_node2 = child3.insert_copy_before(child2, child3);
    pugi::xml_node child4 = copied_node2.child("child4");
    pugi::xml_node child5 = child4.child("child5");
    pugi::xml_node child6 = child5.child("child6");
    pugi::xml_node copied_node3 = child6.insert_copy_before(child5, child6);
    pugi::xml_node child7 = copied_node3.child("child7");
    pugi::xml_node first_child = child7.first_child();
    const char* name = first_child.name();
    pugi::xml_node child8 = first_child.child("child8");
    pugi::xml_node copied_node4 = child8.insert_copy_before(child7, child8);
    pugi::xml_node child9 = copied_node4.child("child9");
    pugi::xml_node first_child2 = child9.first_child();
    pugi::xml_node child10 = first_child2.child("child10");
    pugi::xml_node last_child = child10.last_child();
    const char* name2 = last_child.name();
    pugi::xml_node child11 = last_child.child("child11");
    pugi::xml_node copied_node5 = child11.insert_copy_before(child10, child11);
    pugi::xml_node child12 = copied_node5.child("child12");
    pugi::xml_node first_child3 = child12.first_child();
    pugi::xml_node next_sibling = first_child3.next_sibling();
    pugi::xml_node child13 = next_sibling.child("child13");
    pugi::xml_node first_child4 = child13.first_child();
    const char* value = first_child4.value();

    return 0;
}