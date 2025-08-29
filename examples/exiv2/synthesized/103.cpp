// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpTextValue::size at value.cpp:518:22 in value.hpp
// Exiv2::XmpValue::size at value.cpp:468:18 in value.hpp
// Exiv2::XmpValue::read at value.cpp:463:15 in value.hpp
// Exiv2::XmpValue::size at value.cpp:468:18 in value.hpp
// Exiv2::XmpValue::copy at value.cpp:454:18 in value.hpp
// Exiv2::Xmpdatum::setValue at xmp.cpp:404:16 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::size at xmp.cpp:352:18 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::count at xmp.cpp:348:18 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::size at xmp.cpp:352:18 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::count at xmp.cpp:348:18 in xmp_exiv2.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/value.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create XmpTextValue
        std::string inputStr(reinterpret_cast<const char*>(Data), Size);
        Exiv2::XmpTextValue textValue(inputStr);

        // Test XmpTextValue::size()
        textValue.size();

        // Create XmpValue from textValue
        Exiv2::XmpValue& xmpValue = textValue;

        // Test XmpValue::size()
        xmpValue.size();

        // Test XmpValue::read()
        xmpValue.read(Data, Size);

        // Test XmpValue::copy()
        std::vector<Exiv2::byte> buf(xmpValue.size());
        if (!buf.empty()) {
            xmpValue.copy(buf.data());
        }

        // Create Xmpdatum with dummy key
        Exiv2::XmpKey key("Xmp.dummy");
        Exiv2::Xmpdatum xmpDatum(key);
        xmpDatum.setValue(&xmpValue);

        // Test Xmpdatum::size()
        xmpDatum.size();

        // Test Xmpdatum::count()
        xmpDatum.count();

        // Test copy constructor
        Exiv2::Xmpdatum xmpDatumCopy(xmpDatum);
        xmpDatumCopy.size();
        xmpDatumCopy.count();

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}