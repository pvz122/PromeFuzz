// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpTextValue::read at value.cpp:481:19 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpTextValue::read at value.cpp:481:19 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpTextValue::read at value.cpp:481:19 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpTextValue::read at value.cpp:481:19 in value.hpp
// Exiv2::XmpValue::setXmpArrayType at value.cpp:420:16 in value.hpp
// Exiv2::XmpValue::setXmpArrayType at value.cpp:420:16 in value.hpp
// Exiv2::XmpValue::setXmpArrayType at value.cpp:420:16 in value.hpp
// Exiv2::XmpValue::setXmpArrayType at value.cpp:420:16 in value.hpp
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
#include <string>

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 10) return 0;

    try {
        Exiv2::XmpData xmpData;
        Exiv2::XmpTextValue xmpTextValue1;
        Exiv2::XmpTextValue xmpTextValue2;
        Exiv2::XmpTextValue xmpTextValue3;
        Exiv2::XmpTextValue xmpTextValue4;

        std::string key1("Xmp.test.key1");
        std::string key2("Xmp.test.key2");
        std::string key3("Xmp.test.key3");
        std::string key4("Xmp.test.key4");

        std::string buf1(reinterpret_cast<const char*>(Data), Size / 4);
        std::string buf2(reinterpret_cast<const char*>(Data + Size / 4), Size / 4);
        std::string buf3(reinterpret_cast<const char*>(Data + Size / 2), Size / 4);
        std::string buf4(reinterpret_cast<const char*>(Data + 3 * Size / 4), Size / 4);

        Exiv2::XmpKey xmpKey1(key1);
        Exiv2::XmpKey xmpKey2(key2);
        Exiv2::XmpKey xmpKey3(key3);
        Exiv2::XmpKey xmpKey4(key4);

        xmpData.add(xmpKey1, &xmpTextValue1);
        xmpTextValue1.read(buf1);
        xmpData.add(xmpKey2, &xmpTextValue2);
        xmpTextValue2.read(buf2);
        xmpData.add(xmpKey3, &xmpTextValue3);
        xmpTextValue3.read(buf3);
        xmpData.add(xmpKey4, &xmpTextValue4);
        xmpTextValue4.read(buf4);

        xmpTextValue1.setXmpArrayType(Exiv2::XmpValue::xaAlt);
        xmpTextValue2.setXmpArrayType(Exiv2::XmpValue::xaBag);
        xmpTextValue3.setXmpArrayType(Exiv2::XmpValue::xaSeq);
        xmpTextValue4.setXmpArrayType(Exiv2::XmpValue::xaNone);
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}