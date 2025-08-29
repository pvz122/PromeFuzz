// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xpath_variable_set::set at pugixml.cpp:13171:40 in pugixml.hpp
// pugi::xpath_variable_set::set at pugixml.cpp:13177:40 in pugixml.hpp
// pugi::xpath_variable_set::set at pugixml.cpp:13183:40 in pugixml.hpp
// pugi::xpath_variable_set::set at pugixml.cpp:13189:40 in pugixml.hpp
// pugi::xml_document::load_buffer at pugixml.cpp:7746:46 in pugixml.hpp
// pugi::xml_document::document_element at pugixml.cpp:7827:38 in pugixml.hpp
// pugi::xml_node::select_nodes at pugixml.cpp:13454:40 in pugixml.hpp
// pugi::xpath_variable_set::get at pugixml.cpp:13195:51 in pugixml.hpp
// pugi::xpath_variable_set::get at pugixml.cpp:13195:51 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + sizeof(bool) + 1) return 0;

    pugi::xpath_variable_set variables;
    pugi::xpath_node_set node_set;

    bool bool_val = *reinterpret_cast<const bool*>(Data);
    double double_val = *reinterpret_cast<const double*>(Data + sizeof(bool));
    
    // Ensure the string value is null-terminated and within bounds
    size_t str_len = Size - (sizeof(bool) + sizeof(double));
    char* str_val = new char[str_len + 1];
    std::memcpy(str_val, Data + sizeof(bool) + sizeof(double), str_len);
    str_val[str_len] = '\0';

    variables.set("bool_var", bool_val);
    variables.set("double_var", double_val);
    variables.set("str_var", str_val);
    variables.set("node_set_var", node_set);

    pugi::xml_document doc;
    if (!doc.load_buffer(Data, Size)) {
        delete[] str_val;
        return 0;
    }

    pugi::xml_node root = doc.document_element();
    if (!root) {
        delete[] str_val;
        return 0;
    }

    root.select_nodes("//node", &variables);

    const pugi::xpath_variable* var_bool = variables.get("bool_var");
    const pugi::xpath_variable* var_double = variables.get("double_var");

    delete[] str_val;
    return 0;
}