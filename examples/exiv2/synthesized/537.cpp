// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1092:15 in value.hpp
// Exiv2::ValueType<double>::toUint32 at value.hpp:1588:36 in value.hpp
// Exiv2::ValueType<std::pair<unsigned int, unsigned int>>::toUint32 at value.hpp:1615:39 in value.hpp
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
#include <cstdint>
#include <utility>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput_537(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Initialize ValueType<double>
    Exiv2::ValueType<double> doubleVal;
    try {
        doubleVal.toUint32(Data[0] % 10);
    } catch (...) {}

    // Initialize ValueType<std::pair<unsigned int, unsigned int>>
    unsigned int first = Size > 0 ? Data[0] : 0;
    unsigned int second = Size > 1 ? Data[1] : 0;
    std::pair<unsigned int, unsigned int> uintPair = {first, second};
    Exiv2::ValueType<std::pair<unsigned int, unsigned int>> uintPairVal(uintPair);
    try {
        uintPairVal.toUint32(Data[0] % 2);
    } catch (...) {}

    // Initialize ValueType<float>
    Exiv2::ValueType<float> floatVal;
    try {
        floatVal.toUint32(Data[0] % 10);
    } catch (...) {}

    return 0;
}