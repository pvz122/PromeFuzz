// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpProperties::nsInfo at properties.cpp:5069:33 in properties.hpp
// Exiv2::XmpProperties::unregisterNs at properties.cpp:4969:21 in properties.hpp
// Exiv2::XmpProperties::prefix at properties.cpp:4993:28 in properties.hpp
// Exiv2::XmpProperties::registeredNamespaces at properties.cpp:5084:21 in properties.hpp
// Exiv2::XmpProperties::ns at properties.cpp:5008:28 in properties.hpp
// Exiv2::XmpProperties::registerNs at properties.cpp:4941:21 in properties.hpp
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
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_570(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Split input into two parts for namespace and prefix
    size_t split = Size / 2;
    std::string ns(reinterpret_cast<const char*>(Data), split);
    std::string prefix(reinterpret_cast<const char*>(Data + split), Size - split);

    try {
        // Test nsInfo
        try {
            const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo(prefix);
            (void)info; // Avoid unused variable warning
        } catch (const Exiv2::Error&) {}

        // Test unregisterNs
        Exiv2::XmpProperties::unregisterNs(ns);

        // Test prefix
        std::string p = Exiv2::XmpProperties::prefix(ns);
        (void)p; // Avoid unused variable warning

        // Test registeredNamespaces
        Exiv2::Dictionary nsDict;
        Exiv2::XmpProperties::registeredNamespaces(nsDict);

        // Test ns
        try {
            std::string n = Exiv2::XmpProperties::ns(prefix);
            (void)n; // Avoid unused variable warning
        } catch (const Exiv2::Error&) {}

        // Test registerNs
        Exiv2::XmpProperties::registerNs(ns, prefix);

    } catch (const Exiv2::Error&) {
        // Ignore all Exiv2 exceptions
    }

    return 0;
}