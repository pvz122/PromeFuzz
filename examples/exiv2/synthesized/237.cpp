// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpProperties::nsInfo at properties.cpp:5069:33 in properties.hpp
// Exiv2::XmpProperties::registerNs at properties.cpp:4941:21 in properties.hpp
// Exiv2::XmpProperties::registerNs at properties.cpp:4941:21 in properties.hpp
// Exiv2::XmpProperties::unregisterNs at properties.cpp:4969:21 in properties.hpp
// Exiv2::XmpProperties::prefix at properties.cpp:4993:28 in properties.hpp
// Exiv2::XmpProperties::printProperties at properties.cpp:5091:21 in properties.hpp
// Exiv2::XmpProperties::ns at properties.cpp:5008:28 in properties.hpp
// Exiv2::XmpProperties::unregisterNs at properties.cpp:4969:21 in properties.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/properties.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput_237(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    std::string input(reinterpret_cast<const char*>(Data), Size);
    std::string ns1 = "http://ns.example.com/ns1/";
    std::string prefix1 = "prefix1";
    std::string ns2 = "http://ns.example.com/ns2/";
    std::string prefix2 = "prefix2";

    try {
        // Test nsInfo
        try {
            Exiv2::XmpProperties::nsInfo(input.substr(0, Size/2));
        } catch (const Exiv2::Error&) {}

        // Test registerNs and unregisterNs
        Exiv2::XmpProperties::registerNs(ns1, prefix1);
        Exiv2::XmpProperties::registerNs(ns2, prefix2);
        Exiv2::XmpProperties::unregisterNs(ns1);

        // Test prefix
        Exiv2::XmpProperties::prefix(ns2);

        // Test printProperties
        std::ofstream dummyOut("./dummy_file");
        Exiv2::XmpProperties::printProperties(dummyOut, prefix2);
        dummyOut.close();

        // Test ns
        try {
            Exiv2::XmpProperties::ns(prefix2);
        } catch (const Exiv2::Error&) {}

        // Cleanup
        Exiv2::XmpProperties::unregisterNs(ns2);
    } catch (const Exiv2::Error&) {
        // Ignore all Exiv2 exceptions
    }

    return 0;
}