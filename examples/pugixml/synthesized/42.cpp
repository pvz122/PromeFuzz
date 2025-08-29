// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xpath_variable_set::add at pugixml.cpp:13148:51 in pugixml.hpp
// pugi::xpath_variable::get_string at pugixml.cpp:12965:45 in pugixml.hpp
// pugi::xpath_variable::get_node_set at pugixml.cpp:12971:53 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:12976:36 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:12984:36 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:12992:36 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:13013:36 in pugixml.hpp
// pugi::xpath_variable::get_boolean at pugixml.cpp:12955:36 in pugixml.hpp
// pugi::xpath_variable::get_number at pugixml.cpp:12960:38 in pugixml.hpp
// pugi::xpath_variable::get_string at pugixml.cpp:12965:45 in pugixml.hpp
// pugi::xpath_variable::get_node_set at pugixml.cpp:12971:53 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xpath_variable_set vars;
    pugi::xpath_variable* var = vars.add("var", pugi::xpath_type_string);
    pugi::xpath_node_set node_set;
    bool bool_val = *Data % 2 == 0;
    double num_val = static_cast<double>(*Data);

    // Ensure the string is null-terminated
    std::vector<char> str_data(Data, Data + Size);
    str_data.push_back('\0');
    const char* str = str_data.data();

    var->get_string();
    var->get_node_set();
    var->set(bool_val);
    var->set(num_val);
    var->set(str);
    var->set(node_set);
    var->get_boolean();
    var->get_number();
    var->get_string();
    var->get_node_set();

    return 0;
}