// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::l2Data at types.cpp:389:8 in types.hpp
// Exiv2::DataValue::read at value.cpp:110:16 in value.hpp
// Exiv2::DataValue::read at value.cpp:104:16 in value.hpp
// Exiv2::toData at value.hpp:1420:15 in value.hpp
// Exiv2::ValueType::copy at value.hpp:1527:22 in value.hpp
// Exiv2::ValueType::setDataArea at value.hpp:1684:19 in value.hpp
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
#include <string>

template<>
unsigned long Exiv2::toData<Exiv2::byte>(Exiv2::byte* buf, Exiv2::byte t, Exiv2::ByteOrder byteOrder) {
    if (buf) buf[0] = t;
    return 1;
}

template<>
Exiv2::byte Exiv2::getValue<Exiv2::byte>(const Exiv2::byte* buf, Exiv2::ByteOrder byteOrder) {
    return buf ? buf[0] : 0;
}

extern "C" int LLVMFuzzerTestOneInput_524(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    Exiv2::ByteOrder byteOrder = Size % 2 ? Exiv2::littleEndian : Exiv2::bigEndian;
    int32_t l = static_cast<int32_t>(Size);
    const size_t buf_size = std::min(Size, (size_t)1024);
    Exiv2::byte* buf = new Exiv2::byte[buf_size]();
    std::string str(reinterpret_cast<const char*>(Data), buf_size);

    if (Size >= 4) {
        Exiv2::l2Data(buf, l, byteOrder);
    }

    try {
        Exiv2::DataValue dataValue;

        if (!str.empty()) {
            dataValue.read(str);
        }

        if (Size > 8) {
            dataValue.read(Data, buf_size);
        }

        if (Size >= 4) {
            Exiv2::toData(buf, l, byteOrder);
        }
    } catch (...) {
    }

    try {
        if (Size > 0) {
            Exiv2::ValueType<Exiv2::byte> valueType(Data, buf_size, byteOrder, Exiv2::unsignedByte);

            if (Size >= 1) {
                valueType.copy(buf, byteOrder);
            }

            if (Size > 4) {
                valueType.setDataArea(Data, std::min(Size/2, (size_t)1024));
            }
        }
    } catch (...) {
    }

    delete[] buf;
    return 0;
}