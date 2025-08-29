// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toRational at value.hpp:1648:38 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
// Exiv2::ValueType<float>::toRational at value.hpp:1660:35 in value.hpp
// Exiv2::ValueType::toRational at value.hpp:1642:24 in value.hpp
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
#include <cstdint>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_137(const uint8_t *Data, size_t Size) {
    if (Size < 8) return 0;

    // Create test values from fuzzer input
    unsigned int u1 = *reinterpret_cast<const unsigned int*>(Data);
    unsigned int u2 = *reinterpret_cast<const unsigned int*>(Data + 4);
    int i1 = *reinterpret_cast<const int*>(Data);
    int i2 = *reinterpret_cast<const int*>(Data + 4);
    float f = *reinterpret_cast<const float*>(Data);
    double d = *reinterpret_cast<const double*>(Data);
    size_t n = Size % 10; // Limit n to small values

    try {
        // Test ValueType<std::pair<unsigned int, unsigned int>>::toRational
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> v1(std::make_pair(u1, u2));
        (void)v1.toRational(n);

        // Test ValueType<std::pair<int, int>>::toRational
        Exiv2::ValueType<std::pair<int, int>> v2(std::make_pair(i1, i2));
        (void)v2.toRational(n);

        // Test ValueType<double>::toRational
        Exiv2::ValueType<double> v3(d);
        (void)v3.toRational(n);

        // Test ValueType<float>::toRational
        Exiv2::ValueType<float> v4(f);
        (void)v4.toRational(n);

        // Test ValueType::toRational through concrete type
        Exiv2::ValueType<int> v5(42);
        (void)v5.toRational(n);

    } catch (...) {
        // Catch all exceptions to prevent crashes
    }

    return 0;
}