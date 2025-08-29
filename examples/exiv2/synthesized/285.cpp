// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
// Exiv2::XmpData::begin at xmp.cpp:472:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::findKey at xmp.cpp:444:28 in xmp_exiv2.hpp
// Exiv2::XmpData::end at xmp.cpp:476:28 in xmp_exiv2.hpp
// Exiv2::XmpData::erase at xmp.cpp:480:28 in xmp_exiv2.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::XmpData::add at xmp.cpp:431:14 in xmp_exiv2.hpp
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
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_285(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        Exiv2::XmpData xmpData;

        // Add some dummy data to manipulate
        Exiv2::XmpKey key("Xmp.dc.title");
        std::unique_ptr<Exiv2::Value> value = Exiv2::Value::create(Exiv2::xmpText);
        value->read("Test Value");
        xmpData.add(key, value.get());

        // Test begin() and end()
        auto beginIt = xmpData.begin();
        auto endIt = xmpData.end();

        // Test findKey()
        const auto constFindIt = xmpData.findKey(key);
        auto mutableFindIt = xmpData.findKey(key);

        // Test erase() if we found something
        if (mutableFindIt != xmpData.end()) {
            xmpData.erase(mutableFindIt);
        }

        // Add more data based on fuzzer input
        std::string inputStr(reinterpret_cast<const char*>(Data), Size);
        if (!inputStr.empty()) {
            size_t keyLen = std::min(static_cast<size_t>(20), inputStr.size());
            Exiv2::XmpKey fuzzKey(inputStr.substr(0, keyLen));
            std::unique_ptr<Exiv2::Value> fuzzValue = Exiv2::Value::create(Exiv2::xmpText);
            fuzzValue->read(inputStr.c_str());
            xmpData.add(fuzzKey, fuzzValue.get());
        }

    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}