// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::first_child at pugixml.cpp:5961:34 in pugixml.hpp
// pugi::xml_node::last_child at pugixml.cpp:5967:34 in pugixml.hpp
// pugi::xml_node::prepend_move at pugixml.cpp:6480:34 in pugixml.hpp
// pugi::xml_node::prepend_move at pugixml.cpp:6480:34 in pugixml.hpp
// pugi::xml_node::append_move at pugixml.cpp:6464:34 in pugixml.hpp
// pugi::xml_node::append_move at pugixml.cpp:6464:34 in pugixml.hpp
// pugi::xml_node::insert_move_before at pugixml.cpp:6514:34 in pugixml.hpp
// pugi::xml_node::insert_move_before at pugixml.cpp:6514:34 in pugixml.hpp
// pugi::xml_node::insert_move_after at pugixml.cpp:6496:34 in pugixml.hpp
// pugi::xml_node::insert_move_after at pugixml.cpp:6496:34 in pugixml.hpp
// pugi::xml_node::append_move at pugixml.cpp:6464:34 in pugixml.hpp
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
#include <cstdlib>
#include <cstring>
#include <string_view>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.document_element();
    if (!root) return 0;

    pugi::xml_node child1 = root.child("child1");
    pugi::xml_node child2 = root.child("child2");

    pugi::xml_node first_child = root.first_child();
    pugi::xml_node last_child = root.last_child();

    pugi::xml_node prepend_move1 = root.prepend_move(child1);
    pugi::xml_node prepend_move2 = root.prepend_move(child2);

    pugi::xml_node append_move1 = root.append_move(child1);
    pugi::xml_node append_move2 = root.append_move(child2);

    pugi::xml_node insert_move_before1 = root.insert_move_before(child1, child2);
    pugi::xml_node insert_move_before2 = root.insert_move_before(child2, child1);

    pugi::xml_node insert_move_after1 = root.insert_move_after(child1, child2);
    pugi::xml_node insert_move_after2 = root.insert_move_after(child2, child1);

    pugi::xml_node append_move3 = root.append_move(child1);

    return 0;
}