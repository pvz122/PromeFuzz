// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1117:15 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toInt64 at value.hpp:1602:37 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toInt64 at value.hpp:1602:37 in value.hpp
// Exiv2::ValueType<float>::toInt64 at value.hpp:1593:34 in value.hpp
// Exiv2::XmpTextValue::toInt64 at value.cpp:558:23 in value.hpp
// Exiv2::ValueType::toInt64 at value.hpp:1570:23 in value.hpp
// Exiv2::Iptcdatum::toInt64 at iptc.cpp:140:20 in iptc.hpp
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
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_544(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz Exiv2::ValueType<std::pair<int, int>>::toInt64
    {
        std::pair<int, int> pair_data = {static_cast<int>(Data[0]), static_cast<int>(Data[1 % Size])};
        Exiv2::ValueType<std::pair<int, int>> value_pair(pair_data);
        try {
            value_pair.toInt64(0);
            value_pair.toInt64(1);
        } catch (...) {}
    }

    // Fuzz Exiv2::ValueType<float>::toInt64
    {
        float float_data = static_cast<float>(Data[0]);
        Exiv2::ValueType<float> value_float(float_data);
        try {
            value_float.toInt64();
        } catch (...) {}
    }

    // Fuzz Exiv2::XmpTextValue::toInt64
    {
        Exiv2::XmpTextValue xmp_text;
        try {
            xmp_text.toInt64();
        } catch (...) {}
    }

    // Fuzz Exiv2::ValueType::toInt64
    {
        Exiv2::ValueType<int> value_type(static_cast<int>(Data[0]));
        try {
            value_type.toInt64();
        } catch (...) {}
    }

    // Fuzz Exiv2::Iptcdatum::toInt64
    {
        Exiv2::IptcKey key("Iptc.Application2.Keywords");
        Exiv2::Iptcdatum iptc_datum(key);
        try {
            iptc_datum.toInt64();
        } catch (...) {}
    }

    // Fuzz Exiv2::ValueType<double>::toInt64
    {
        double double_data = static_cast<double>(Data[0]);
        Exiv2::ValueType<double> value_double(double_data);
        try {
            value_double.toInt64();
        } catch (...) {}
    }

    return 0;
}