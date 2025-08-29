// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xpath_variable_set::add at pugixml.cpp:13148:51 in pugixml.hpp
// pugi::xpath_variable::type at pugixml.cpp:12950:48 in pugixml.hpp
// pugi::xpath_variable::name at pugixml.cpp:12928:45 in pugixml.hpp
// pugi::xpath_variable::get_boolean at pugixml.cpp:12955:36 in pugixml.hpp
// pugi::xpath_variable::get_number at pugixml.cpp:12960:38 in pugixml.hpp
// pugi::xpath_variable::get_string at pugixml.cpp:12965:45 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xpath_variable_set vars;
    const char* name = "var_name";
    pugi::xpath_value_type type = static_cast<pugi::xpath_value_type>(Data[0] % 5);

    pugi::xpath_variable* var = vars.add(name, type);
    if (!var) return 0;

    var->type();
    var->name();
    var->get_boolean();
    var->get_number();
    var->get_string();

    return 0;
}