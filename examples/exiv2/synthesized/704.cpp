// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1107:15 in value.hpp
// Exiv2::ValueType::toFloat at value.hpp:1620:21 in value.hpp
// Exiv2::Xmpdatum::toFloat at xmp.cpp:368:17 in xmp_exiv2.hpp
// Exiv2::XmpArrayValue::toFloat at value.cpp:617:22 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat at value.hpp:1634:36 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toFloat at value.hpp:1626:35 in value.hpp
// Exiv2::TimeValue::toFloat at value.cpp:1050:18 in value.hpp
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
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_704(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize dummy data
    Exiv2::byte buf[Size];
    for (size_t i = 0; i < Size; ++i) {
        buf[i] = Data[i];
    }

    try {
        // Test Exiv2::ValueType::toFloat
        {
            Exiv2::ValueType<int> valueType(buf, Size, Exiv2::littleEndian);
            (void)valueType.toFloat();
        }

        // Test Exiv2::Xmpdatum::toFloat
        {
            Exiv2::XmpKey key("Xmp.dc.title");
            Exiv2::Xmpdatum xmpdatum(key);
            (void)xmpdatum.toFloat();
        }

        // Test Exiv2::XmpArrayValue::toFloat
        {
            Exiv2::XmpArrayValue xmpArrayValue(Exiv2::xmpBag);
            (void)xmpArrayValue.toFloat();
        }

        // Test Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toFloat
        {
            std::pair<unsigned int, unsigned int> pairData = {0, 0};
            Exiv2::ValueType<std::pair<unsigned int, unsigned int>> valueTypePair(
                reinterpret_cast<Exiv2::byte*>(&pairData), sizeof(pairData), Exiv2::littleEndian);
            (void)valueTypePair.toFloat();
        }

        // Test Exiv2::ValueType<std::pair<int, int>>::toFloat
        {
            std::pair<int, int> pairData = {0, 0};
            Exiv2::ValueType<std::pair<int, int>> valueTypePair(
                reinterpret_cast<Exiv2::byte*>(&pairData), sizeof(pairData), Exiv2::littleEndian);
            (void)valueTypePair.toFloat();
        }

        // Test Exiv2::TimeValue::toFloat
        {
            Exiv2::TimeValue timeValue;
            (void)timeValue.toFloat();
        }
    } catch (...) {
        // Ignore all exceptions
    }

    return 0;
}