// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Value::typeId at value.hpp:85:10 in value.hpp
// Exiv2::Exifdatum::typeId at exif.cpp:316:19 in exif.hpp
// Exiv2::Iptcdatum::typeId at iptc.cpp:112:19 in iptc.hpp
// Exiv2::getType at value.hpp:1082:15 in value.hpp
// Exiv2::getType at value.hpp:1087:15 in value.hpp
// Exiv2::getType at value.hpp:1097:15 in value.hpp
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::TypeInfo::typeName at types.cpp:71:23 in types.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
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
#include <exiv2/types.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/exif.hpp>
#include <cstdint>
#include <vector>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_143(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz Exiv2::Value::typeId
    {
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId));
        if (value.get()) {
            value->typeId();
        }
    }

    // Fuzz Exiv2::Exifdatum::typeId
    {
        Exiv2::ExifKey key("Exif.Image.DateTime");
        Exiv2::Exifdatum datum(key);
        datum.typeId();
    }

    // Fuzz Exiv2::Iptcdatum::typeId
    {
        Exiv2::IptcKey key("Iptc.Application2.Caption");
        Exiv2::Iptcdatum datum(key);
        datum.typeId();
    }

    // Fuzz Exiv2::getType
    {
        Exiv2::getType<uint16_t>();
        Exiv2::getType<uint32_t>();
        Exiv2::getType<int16_t>();
        Exiv2::getType<int32_t>();
    }

    // Fuzz Exiv2::TypeInfo::typeName
    {
        Exiv2::TypeInfo::typeName(static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId));
    }

    // Fuzz Exiv2::Value::create with various types
    {
        for (int i = 0; i < 20; ++i) {
            Exiv2::Value::UniquePtr value = Exiv2::Value::create(static_cast<Exiv2::TypeId>(i));
        }
    }

    return 0;
}