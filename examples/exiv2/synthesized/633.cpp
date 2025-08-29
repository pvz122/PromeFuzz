// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::DataValue::size at value.cpp:129:19 in value.hpp
// Exiv2::DataValue::copy at value.cpp:124:19 in value.hpp
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

extern "C" int LLVMFuzzerTestOneInput_633(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    // Initialize variables
    int32_t l = *reinterpret_cast<const int32_t*>(Data);
    Exiv2::ByteOrder byteOrder = (Data[0] % 2) ? Exiv2::littleEndian : Exiv2::bigEndian;

    // Create DataValue object
    Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(Data[1] % Exiv2::lastTypeId);
    Exiv2::DataValue dataValue(Data, Size, byteOrder, typeId);

    // Create properly sized buffer for copy operation
    Exiv2::byte* buf = new Exiv2::byte[dataValue.size()];
    
    // Test DataValue::copy with correctly sized buffer
    dataValue.copy(buf, byteOrder);
    
    delete[] buf;

    return 0;
}