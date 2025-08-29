// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::DataBuf::data at types.cpp:171:23 in types.hpp
// Exiv2::DataBuf::size at types.hpp:168:24 in types.hpp
// Exiv2::Iptcdatum::tagDesc at iptc.cpp:104:24 in iptc.hpp
// Exiv2::Iptcdatum::key at iptc.cpp:76:24 in iptc.hpp
// Exiv2::Iptcdatum::recordName at iptc.cpp:80:24 in iptc.hpp
// Exiv2::Iptcdatum::groupName at iptc.cpp:92:24 in iptc.hpp
// Exiv2::Iptcdatum::toString at iptc.cpp:132:24 in iptc.hpp
// Exiv2::Iptcdatum::tagName at iptc.cpp:96:24 in iptc.hpp
// Exiv2::Iptcdatum::tagDesc at iptc.cpp:104:24 in iptc.hpp
// Exiv2::Iptcdatum::key at iptc.cpp:76:24 in iptc.hpp
// Exiv2::Iptcdatum::recordName at iptc.cpp:80:24 in iptc.hpp
// Exiv2::Iptcdatum::groupName at iptc.cpp:92:24 in iptc.hpp
// Exiv2::Iptcdatum::toString at iptc.cpp:132:24 in iptc.hpp
// Exiv2::Iptcdatum::tagName at iptc.cpp:96:24 in iptc.hpp
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
#include <fstream>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_133(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Create a dummy IPTC data entry
        Exiv2::DataBuf buffer(Size);
        std::memcpy(buffer.data(), Data, Size);
        Exiv2::IptcKey key("Iptc.Application2.ObjectName");
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
        value->read(buffer.data(), buffer.size(), Exiv2::invalidByteOrder);
        Exiv2::Iptcdatum datum(key, value.get());

        // Call target functions
        (void)datum.tagDesc();
        (void)datum.key();
        (void)datum.recordName();
        (void)datum.groupName();
        (void)datum.toString();
        (void)datum.tagName();

        // Test copy constructor
        Exiv2::Iptcdatum copiedDatum(datum);
        (void)copiedDatum.tagDesc();
        (void)copiedDatum.key();
        (void)copiedDatum.recordName();
        (void)copiedDatum.groupName();
        (void)copiedDatum.toString();
        (void)copiedDatum.tagName();
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}