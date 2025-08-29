// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Xmpdatum::setValue at xmp.cpp:404:16 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::Xmpdatum::value at xmp.cpp:380:24 in xmp_exiv2.hpp
// Exiv2::Value::ok at value.hpp:181:8 in value.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
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
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpData xmpData;
        Exiv2::XmpKey key("Xmp.dummy.key");
        Exiv2::Xmpdatum xmpDatum(key);

        // Populate xmpDatum with some data
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::asciiString);
        value->read(Data, Size, Exiv2::littleEndian);
        xmpDatum.setValue(value.get());

        // Invoke functions in specified order
        xmpDatum.value().ok();
        xmpDatum.value();
        xmpDatum.value().ok();
        xmpDatum.value().ok();
        xmpDatum.value().ok();
        xmpDatum.value();
        xmpDatum.value().ok();
        xmpDatum.value().ok();
        xmpDatum.value().ok();
        xmpDatum.value();
        xmpDatum.value().ok();
        xmpDatum.value().ok();
        xmpDatum.value().ok();
        xmpDatum.value();
        xmpDatum.value().ok();
        xmpDatum.value();
        xmpDatum.value().ok();
        xmpDatum.value().ok();
        xmpDatum.value().ok();
        xmpData.findKey(key);
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}