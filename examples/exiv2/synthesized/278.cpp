// This fuzz driver is generated for library exiv2, aiming to fuzz the following functions:
// Exiv2::Value::create at value.cpp:22:25 in value.hpp
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
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_278(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize with fuzz data
    Exiv2::ByteOrder byteOrder = static_cast<Exiv2::ByteOrder>(Data[0] % 3);
    Exiv2::TypeId typeId = static_cast<Exiv2::TypeId>(Data[0] % Exiv2::lastTypeId);
    const Exiv2::byte* buf = Data + 1;
    size_t len = Size - 1;

    try {
        // Create Value instance with specific type
        Exiv2::Value::UniquePtr value = Exiv2::Value::create(typeId);
        
        // Test setDataArea()
        if (len > 0) {
            value->setDataArea(buf, len);
        }

        // Test size()
        value->size();
        value->sizeDataArea();

        // Test copy()
        if (value->size() > 0) {
            Exiv2::byte* copyBuf = new Exiv2::byte[value->size()];
            value->copy(copyBuf, byteOrder);
            delete[] copyBuf;
        }

    } catch (...) {
        // Handle exceptions
    }

    return 0;
}