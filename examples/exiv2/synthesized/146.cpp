// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Iptcdatum::tag at iptc.cpp:108:21 in iptc.hpp
// Exiv2::Iptcdatum::typeName at iptc.cpp:116:24 in iptc.hpp
// Exiv2::Iptcdatum::count at iptc.cpp:124:19 in iptc.hpp
// Exiv2::Iptcdatum::familyName at iptc.cpp:88:24 in iptc.hpp
// Exiv2::Iptcdatum::setValue at iptc.cpp:195:17 in iptc.hpp
// Exiv2::Iptcdatum::value at iptc.cpp:156:25 in iptc.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::Iptcdatum::setValue at iptc.cpp:195:17 in iptc.hpp
// Exiv2::Iptcdatum::value at iptc.cpp:156:25 in iptc.hpp
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <exiv2/iptc.hpp>
#include <exiv2/error.hpp>
#include <cstdint>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::IptcKey key("Iptc.Application2.Keywords");
        Exiv2::Iptcdatum datum(key);

        // Test tag()
        (void)datum.tag();

        // Test typeName()
        (void)datum.typeName();

        // Test count()
        (void)datum.count();

        // Test familyName()
        (void)datum.familyName();

        // Test setValue() with a string value
        std::string strValue(reinterpret_cast<const char*>(Data), Size);
        Exiv2::StringValue value(strValue);
        datum.setValue(&value);

        // Test value()
        try {
            (void)datum.value();
        } catch (const Exiv2::Error&) {
            // Ignore exceptions from value()
        }

        // Test setValue() with a DataValue
        Exiv2::DataValue dataValue(Exiv2::undefined);
        dataValue.read(Data, Size);
        datum.setValue(&dataValue);

        // Test value() again
        try {
            (void)datum.value();
        } catch (const Exiv2::Error&) {
            // Ignore exceptions from value()
        }

    } catch (const Exiv2::Error&) {
        // Ignore all exceptions
    }

    return 0;
}