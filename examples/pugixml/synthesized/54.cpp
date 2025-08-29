// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xpath_variable_set::add at pugixml.cpp:13148:51 in pugixml.hpp
// pugi::xpath_variable_set::set at pugixml.cpp:13183:40 in pugixml.hpp
// pugi::xpath_variable_set::get at pugixml.cpp:13195:51 in pugixml.hpp
// pugi::xpath_variable_set::get at pugixml.cpp:13200:57 in pugixml.hpp
// pugi::xpath_variable::name at pugixml.cpp:12928:45 in pugixml.hpp
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
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    pugi::xpath_variable_set vars;

    // Add a variable
    const char* var_name = "test_var";
    pugi::xpath_variable* var = vars.add(var_name, pugi::xpath_type_string);
    if (!var) return 0;

    // Set the variable value
    char* value = new char[Size + 1];
    std::memcpy(value, Data, Size);
    value[Size] = '\0';
    bool set_result = vars.set(var_name, value);
    delete[] value;
    if (!set_result) return 0;

    // Get the variable (non-const version)
    pugi::xpath_variable* var_non_const = vars.get(var_name);
    if (!var_non_const) return 0;

    // Get the variable (const version)
    const pugi::xpath_variable_set& vars_const = vars;
    const pugi::xpath_variable* var_const = vars_const.get(var_name);
    if (!var_const) return 0;

    // Get the variable name
    const char* name = var->name();
    if (!name) return 0;

    // Get the string value of the variable
    const char* str_value = var->get_string();
    if (!str_value) return 0;

    return 0;
}