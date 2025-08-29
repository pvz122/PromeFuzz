// This fuzz driver is generated for library pugixml, aiming to fuzz the following functions:
// pugi::xpath_variable_set::add at pugixml.cpp:13148:51 in pugixml.hpp
// pugi::xpath_variable::name at pugixml.cpp:12928:45 in pugixml.hpp
// pugi::xpath_variable::type at pugixml.cpp:12950:48 in pugixml.hpp
// pugi::xpath_variable::set at pugixml.cpp:12992:36 in pugixml.hpp
// pugi::xpath_variable::get_string at pugixml.cpp:12965:45 in pugixml.hpp
// pugi::xpath_query::return_type at pugixml.cpp:13278:45 in pugixml.hpp
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

extern "C" int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        pugi::xpath_variable_set vars;
        pugi::xpath_variable* var = vars.add("test_var", static_cast<pugi::xpath_value_type>(Data[0] % 5));
        if (var) {
            const char* name = var->name();
            pugi::xpath_value_type type = var->type();
            if (type == pugi::xpath_type_string) {
                std::string str(reinterpret_cast<const char*>(Data), Size);
                var->set(str.c_str());
                const char* str_val = var->get_string();
            }
        }

        std::string query_str(reinterpret_cast<const char*>(Data), Size);
        pugi::xpath_query query(query_str.c_str(), &vars);
        pugi::xpath_value_type return_type = query.return_type();
    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}