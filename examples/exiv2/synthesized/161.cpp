// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpProperties::unregisterNs at properties.cpp:4983:21 in properties.hpp
// Exiv2::XmpProperties::registerNs at properties.cpp:4941:21 in properties.hpp
// Exiv2::XmpProperties::prefix at properties.cpp:4993:28 in properties.hpp
// Exiv2::XmpProperties::printProperties at properties.cpp:5091:21 in properties.hpp
// Exiv2::XmpProperties::propertyType at properties.cpp:5025:23 in properties.hpp
// Exiv2::XmpProperties::ns at properties.cpp:5008:28 in properties.hpp
// Exiv2::XmpProperties::unregisterNs at properties.cpp:4983:21 in properties.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/exiv2.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput_161(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    try {
        // Create dummy strings from fuzzer input with minimum length checks
        std::string ns_str(reinterpret_cast<const char*>(Data), Size);
        std::string prefix_str(ns_str.substr(0, std::min(Size/2, Size-1)));
        std::string property_str(ns_str.substr(std::min(Size/2, Size-1)));

        // Ensure strings aren't empty
        if (ns_str.empty()) ns_str = "ns";
        if (prefix_str.empty()) prefix_str = "pfx";
        if (property_str.empty()) property_str = "prop";

        // Ensure namespace ends with '/' or '#'
        if (ns_str.back() != '/' && ns_str.back() != '#') {
            ns_str += '/';
        }

        // Test unregisterNs
        Exiv2::XmpProperties::unregisterNs();

        // Test registerNs with sanitized strings
        Exiv2::XmpProperties::registerNs(ns_str, prefix_str);

        // Test prefix
        Exiv2::XmpProperties::prefix(ns_str);

        // Test printProperties
        std::ostringstream os;
        Exiv2::XmpProperties::printProperties(os, prefix_str);

        // Test propertyType
        Exiv2::XmpKey key(prefix_str, property_str);
        Exiv2::XmpProperties::propertyType(key);

        // Test ns
        try {
            Exiv2::XmpProperties::ns(prefix_str);
        } catch (...) {
            // Ignore exceptions from invalid prefix
        }

        // Clean up
        Exiv2::XmpProperties::unregisterNs();
    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}