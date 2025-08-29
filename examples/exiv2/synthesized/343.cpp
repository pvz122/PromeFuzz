// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1117:15 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toInt64 at value.hpp:1602:37 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toInt64 at value.hpp:1602:37 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
// Exiv2::Iptcdatum::toInt64 at iptc.cpp:140:20 in iptc.hpp
// Exiv2::LangAltValue::toInt64 at value.cpp:721:23 in value.hpp
// Exiv2::ValueType<double>::toInt64 at value.hpp:1583:35 in value.hpp
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
#include <exiv2/iptc.hpp>
#include <memory>

extern "C" int LLVMFuzzerTestOneInput_343(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    try {
        // Test Exiv2::ValueType<std::pair<int, int>>::toInt64
        std::pair<int, int> pair_val = {rand(), rand()};
        Exiv2::ValueType<std::pair<int, int>> pair_value(pair_val);
        pair_value.toInt64(0);
        pair_value.toInt64(1);

        // Test Exiv2::ValueType<float>::toInt64
        float float_val = static_cast<float>(rand()) / RAND_MAX;
        Exiv2::ValueType<float> float_value(float_val);
        float_value.toInt64(0);

        // Test Exiv2::ValueType::toInt64 (generic)
        int int_val = rand();
        Exiv2::ValueType<int> int_value(int_val);
        int_value.toInt64(0);

        // Test Exiv2::Iptcdatum::toInt64
        Exiv2::IptcKey key("Iptc.Application2.Headline");
        std::unique_ptr<Exiv2::Value> value(Exiv2::Value::create(Exiv2::unsignedLong));
        value->read("12345");
        Exiv2::Iptcdatum datum(key, value.get());
        datum.toInt64(0);

        // Test Exiv2::LangAltValue::toInt64
        Exiv2::LangAltValue lang_value("en-US");
        lang_value.toInt64(0);

        // Test Exiv2::ValueType<double>::toInt64
        double double_val = static_cast<double>(rand()) / RAND_MAX;
        Exiv2::ValueType<double> double_value(double_val);
        double_value.toInt64(0);

    } catch (...) {
        // Handle exceptions silently
    }

    return 0;
}