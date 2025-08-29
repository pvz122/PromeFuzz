// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::ValueType<double>::toUint32 at value.hpp:1588:36 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
// Exiv2::Metadatum::toUint32 at metadatum.cpp:16:21 in metadatum.hpp
// Exiv2::ValueType<std::pair<int, int>>::toUint32 at value.hpp:1606:38 in value.hpp
// Exiv2::ValueType::toUint32 at value.hpp:1575:24 in value.hpp
// Exiv2::ValueType<float>::toUint32 at value.hpp:1597:35 in value.hpp
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
#include <exiv2/metadatum.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/exif.hpp>
#include <cstdint>
#include <vector>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) + sizeof(float) + 4) return 0;

    // Initialize with fuzzed data safely
    double double_val = 0.0;
    float float_val = 0.0f;
    memcpy(&double_val, Data, sizeof(double));
    memcpy(&float_val, Data + sizeof(double), sizeof(float));

    // Test ValueType<double>::toUint32
    try {
        Exiv2::ValueType<double> double_value(double_val);
        double_value.toUint32(0);
    } catch (...) {}

    // Test ValueType<std::pair<unsigned int, unsigned int>>::toUint32
    try {
        unsigned int u1 = Data[sizeof(double) + sizeof(float)] % 256;
        unsigned int u2 = Data[sizeof(double) + sizeof(float) + 1] % 256;
        std::pair<unsigned int, unsigned int> uint_pair = {u1, u2};
        Exiv2::ValueType<std::pair<unsigned int, unsigned int>> uint_pair_value(uint_pair);
        uint_pair_value.toUint32(0);
    } catch (...) {}

    // Test Metadatum::toUint32
    try {
        Exiv2::XmpKey key("Xmp.dc.title");
        Exiv2::Xmpdatum datum(key);
        datum.toUint32(0);
    } catch (...) {}

    // Test ValueType<std::pair<int, int>>::toUint32
    try {
        int i1 = static_cast<int>(Data[sizeof(double) + sizeof(float) + 2] % 256);
        int i2 = static_cast<int>(Data[sizeof(double) + sizeof(float) + 3] % 256);
        std::pair<int, int> int_pair = {i1, i2};
        Exiv2::ValueType<std::pair<int, int>> int_pair_value(int_pair);
        int_pair_value.toUint32(0);
    } catch (...) {}

    // Test ValueType::toUint32 (generic)
    try {
        Exiv2::ValueType<int> int_value(Data[0] % 256);
        int_value.toUint32(0);
    } catch (...) {}

    // Test ValueType<float>::toUint32
    try {
        Exiv2::ValueType<float> float_value(float_val);
        float_value.toUint32(0);
    } catch (...) {}

    return 0;
}