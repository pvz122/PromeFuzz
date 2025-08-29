// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::StringValueBase::read at value.cpp:178:22 in value.hpp
// Exiv2::Xmpdatum::toString at xmp.cpp:356:23 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::familyName at xmp.cpp:312:23 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::count at xmp.cpp:348:18 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::key at xmp.cpp:308:23 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::typeName at xmp.cpp:340:23 in xmp_exiv2.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/error.hpp>
#include <fstream>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_345(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy XmpKey
        std::string keyStr("Xmp.dummy.key");
        Exiv2::XmpKey key(keyStr);

        // Create a dummy Value (StringValue)
        Exiv2::StringValue value;
        value.read(std::string(reinterpret_cast<const char*>(Data), Size));

        // Create Xmpdatum object
        Exiv2::Xmpdatum xmpDatum(key, &value);

        // Test the target API functions
        (void)xmpDatum.toString();
        (void)xmpDatum.familyName();
        (void)xmpDatum.count();
        (void)xmpDatum.key();
        
        try {
            (void)xmpDatum.value();
        } catch (const Exiv2::Error&) {
            // Expected if value is not set
        }

        (void)xmpDatum.typeName();

    } catch (const Exiv2::Error&) {
        // Ignore Exiv2 exceptions
    }

    return 0;
}