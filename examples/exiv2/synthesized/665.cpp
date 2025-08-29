// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1112:15 in value.hpp
// Exiv2::ValueType<std::pair<int, int>>::toRational at value.hpp:1648:38 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toRational at value.hpp:1654:39 in value.hpp
// Exiv2::ValueType<double>::toRational at value.hpp:1667:36 in value.hpp
// Exiv2::ValueType<float>::toRational at value.hpp:1660:35 in value.hpp
// Exiv2::Exifdatum::toRational at exif.cpp:352:21 in exif.hpp
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
#include <exiv2/exif.hpp>
#include <cstdint>
#include <cstdlib>
#include <utility>

extern "C" int LLVMFuzzerTestOneInput_665(const uint8_t *Data, size_t Size) {
    if (Size < 2 * sizeof(int)) return 0;

    // Initialize ValueType with pair<int, int>
    int first = *reinterpret_cast<const int*>(Data);
    int second = *reinterpret_cast<const int*>(Data + sizeof(int));
    Exiv2::ValueType<std::pair<int, int>> vt1(std::make_pair(first, second));
    try {
        vt1.toRational();
    } catch (...) {}

    // Initialize ValueType with pair<unsigned int, unsigned int>
    unsigned int ufirst = *reinterpret_cast<const unsigned int*>(Data);
    unsigned int usecond = *reinterpret_cast<const unsigned int*>(Data + sizeof(unsigned int));
    Exiv2::ValueType<std::pair<unsigned int, unsigned int>> vt2(std::make_pair(ufirst, usecond));
    try {
        vt2.toRational();
    } catch (...) {}

    // Initialize ValueType with double
    double dval = *reinterpret_cast<const double*>(Data);
    Exiv2::ValueType<double> vt3(dval);
    try {
        vt3.toRational();
    } catch (...) {}

    // Initialize ValueType with float
    float fval = *reinterpret_cast<const float*>(Data);
    Exiv2::ValueType<float> vt4(fval);
    try {
        vt4.toRational();
    } catch (...) {}

    // Initialize Exifdatum
    Exiv2::ExifKey key("Exif.Image.ImageWidth");
    Exiv2::Exifdatum datum(key);
    try {
        datum.toRational();
    } catch (...) {}

    return 0;
}