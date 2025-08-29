// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::getType at value.hpp:1102:15 in value.hpp
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::toData at value.hpp:1420:15 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
// Exiv2::ValueType::read at value.hpp:1500:19 in value.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
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
#include <exiv2/types.hpp>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_556(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Use vector for dynamic buffer sizing
    std::vector<Exiv2::byte> buf(Size);
    int32_t l = *reinterpret_cast<const int32_t*>(Data);
    Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;

    if (Size >= 4) {
        Exiv2::l2Data(buf.data(), l, byteOrder);
    }

    if (Size >= 4) {
        Exiv2::toData(buf.data(), l, byteOrder);
    }

    Exiv2::DataValue dataValue;

    if (Size >= sizeof(int32_t)) {
        Exiv2::ValueType<int32_t> valueType(Data, Size, byteOrder);

        if (Size >= 4) {
            valueType.copy(buf.data(), byteOrder);
        }

        if (Size > 8) {
            valueType.setDataArea(Data + 4, Size - 4);
        }

        if (Size >= 4) {
            valueType.read(Data, Size, byteOrder);
        }
    }

    if (Size >= 4) {
        dataValue.read(Data, Size);
    }

    return 0;
}