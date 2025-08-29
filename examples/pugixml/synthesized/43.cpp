// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_node::root at pugixml.cpp:5915:34 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xml_node::attribute at pugixml.cpp:5718:39 in pugixml.hpp
// pugi::xml_node::child at pugixml.cpp:5704:34 in pugixml.hpp
// pugi::xpath_query::evaluate_boolean at pugixml.cpp:13285:33 in pugixml.hpp
// pugi::xpath_query::evaluate_number at pugixml.cpp:13306:35 in pugixml.hpp
// pugi::xpath_query::evaluate_string at pugixml.cpp:13328:37 in pugixml.hpp
// pugi::xpath_query::evaluate_string at pugixml.cpp:13350:35 in pugixml.hpp
// pugi::xpath_query::evaluate_node_set at pugixml.cpp:13380:43 in pugixml.hpp
// pugi::xpath_query::evaluate_node at pugixml.cpp:13402:39 in pugixml.hpp
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
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_43(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(Data, Size);
    if (!result) return 0;

    pugi::xml_node root = doc.root();
    pugi::xml_node child1 = root.child("child1");
    pugi::xml_attribute attr = child1.attribute("attr");
    pugi::xml_node child2 = child1.child("child2");

    pugi::xpath_query query("//node");
    pugi::xpath_node xnode(child2);

    bool eval_bool = query.evaluate_boolean(xnode);
    double eval_num = query.evaluate_number(xnode);

    pugi::string_t eval_str1 = query.evaluate_string(xnode);
    char buffer[1024];
    size_t eval_str2 = query.evaluate_string(buffer, sizeof(buffer), xnode);

    pugi::xpath_node_set eval_node_set = query.evaluate_node_set(xnode);
    pugi::xpath_node eval_node = query.evaluate_node(xnode);

    return 0;
}